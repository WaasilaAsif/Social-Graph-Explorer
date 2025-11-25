#ifndef GRAPHLAYOUT_H
#define GRAPHLAYOUT_H

#include "../dsa/graph/Graph.h"
#include "../dsa/utils/Vector2.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/Queue.h"
#include <cmath>

// Graph layout engine for visualization
// Uses simple layer-based positioning (BFS-like)
class GraphLayout {
public:
    // Generate positions for all nodes in the graph
    // Returns HashMap of nodeID -> Vector2 position
    static HashMap<int, Vector2> generateLayout(const Graph& graph, 
                                               float nodeSpacing = 100.0f,
                                               float layerSpacing = 150.0f) {
        HashMap<int, Vector2> positions(100);
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        
        if (allNodes.isEmpty())
            return positions;
        
        // Use BFS-based layering
        HashMap<int, bool> visited(100);
        HashMap<int, int> layer(100);
        Queue<int> queue;
        
        int startNode = allNodes[0];
        queue.enqueue(startNode);
        visited.put(startNode, true);
        layer.put(startNode, 0);
        
        int maxLayer = 0;
        
        // Assign layers using BFS
        while (!queue.isEmpty()) {
            int current = queue.dequeue();
            int currentLayer = layer.get(current);
            maxLayer = (currentLayer > maxLayer) ? currentLayer : maxLayer;
            
            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;
                if (!visited.contains(neighborID)) {
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);
                    layer.put(neighborID, currentLayer + 1);
                }
            }
        }
        
        // Handle disconnected nodes
        for (int i = 0; i < allNodes.size(); ++i) {
            if (!visited.contains(allNodes[i])) {
                layer.put(allNodes[i], maxLayer + 1);
            }
        }
        
        // Count nodes per layer
        HashMap<int, int> nodesInLayer(100);
        for (int i = 0; i < allNodes.size(); ++i) {
            int nodeLayer = layer.get(allNodes[i]);
            int count = nodesInLayer.contains(nodeLayer) ? nodesInLayer.get(nodeLayer) : 0;
            nodesInLayer.put(nodeLayer, count + 1);
        }
        
        // Track current position in each layer
        HashMap<int, int> layerIndex(100);
        for (int i = 0; i <= maxLayer + 1; ++i) {
            layerIndex.put(i, 0);
        }
        
        // Calculate positions
        for (int i = 0; i < allNodes.size(); ++i) {
            int nodeID = allNodes[i];
            int nodeLayer = layer.get(nodeID);
            int nodesInCurrentLayer = nodesInLayer.get(nodeLayer);
            int indexInLayer = layerIndex.get(nodeLayer);
            
            // Center the layer horizontally
            float layerWidth = (nodesInCurrentLayer - 1) * nodeSpacing;
            float startX = -layerWidth / 2.0f;
            
            float x = startX + indexInLayer * nodeSpacing;
            float y = nodeLayer * layerSpacing;
            
            positions.put(nodeID, Vector2(x, y));
            
            // Increment layer index
            layerIndex.put(nodeLayer, indexInLayer + 1);
        }
        
        return positions;
    }
    
    // Generate circular layout
    static HashMap<int, Vector2> generateCircularLayout(const Graph& graph, float radius = 200.0f) {
        HashMap<int, Vector2> positions(100);
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        
        int nodeCount = allNodes.size();
        if (nodeCount == 0)
            return positions;
        
        float angleStep = 2.0f * 3.14159f / nodeCount;
        
        for (int i = 0; i < nodeCount; ++i) {
            float angle = i * angleStep;
            float x = radius * std::cos(angle);
            float y = radius * std::sin(angle);
            
            positions.put(allNodes[i], Vector2(x, y));
        }
        
        return positions;
    }
    
    // Generate force-directed layout (simplified spring model)
    // Robust implementation that prevents NaN values
    static HashMap<int, Vector2> generateForceDirectedLayout(const Graph& graph,
                                                            int iterations = 50,
                                                            float repulsionStrength = 5000.0f,
                                                            float attractionStrength = 0.1f,
                                                            float damping = 0.9f) {
        HashMap<int, Vector2> positions(100);
        HashMap<int, Vector2> velocities(100);
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        
        if (allNodes.isEmpty())
            return positions;
        
        // Initialize positions in a circle with good spacing
        const float PI = 3.14159265359f;
        float angle = 0.0f;
        float radius = 150.0f;
        float angleStep = (2.0f * PI) / allNodes.size();
        
        for (int i = 0; i < allNodes.size(); ++i) {
            float x = radius * std::cos(angle);
            float y = radius * std::sin(angle);
            positions.put(allNodes[i], Vector2(x, y));
            velocities.put(allNodes[i], Vector2(0.0f, 0.0f));
            angle += angleStep;
        }
        
        // Run force-directed simulation
        for (int iter = 0; iter < iterations; ++iter) {
            HashMap<int, Vector2> forces(100);
            
            // Initialize all forces to zero
            for (int i = 0; i < allNodes.size(); ++i) {
                forces.put(allNodes[i], Vector2(0.0f, 0.0f));
            }
            
            // Calculate repulsive forces between ALL pairs of nodes
            for (int i = 0; i < allNodes.size(); ++i) {
                for (int j = i + 1; j < allNodes.size(); ++j) {
                    Vector2 pos1 = positions.get(allNodes[i]);
                    Vector2 pos2 = positions.get(allNodes[j]);
                    
                    Vector2 delta = pos1 - pos2;
                    float distSq = delta.magnitudeSquared();
                    
                    // Prevent division by zero - use minimum distance
                    const float minDistSq = 25.0f; // 5.0^2
                    if (distSq < minDistSq) {
                        distSq = minDistSq;
                    }
                    
                    // Calculate repulsion force (inverse square law)
                    // force = k / distance^2, direction = normalized delta
                    float forceMag = repulsionStrength / distSq;
                    
                    // Limit maximum force to prevent explosion
                    const float maxForce = 100.0f;
                    if (forceMag > maxForce) {
                        forceMag = maxForce;
                    }
                    
                    // Normalize delta safely
                    float dist = std::sqrt(distSq);
                    Vector2 forceDir = delta / dist; // Safe because dist >= 5.0
                    Vector2 force = forceDir * forceMag;
                    
                    // Apply equal and opposite forces
                    forces.put(allNodes[i], forces.get(allNodes[i]) + force);
                    forces.put(allNodes[j], forces.get(allNodes[j]) - force);
                }
            }
            
            // Calculate attractive forces for connected nodes (edges)
            for (int i = 0; i < allNodes.size(); ++i) {
                int nodeID = allNodes[i];
                Vector2 pos1 = positions.get(nodeID);
                
                const LinkedList<Edge>& neighbors = graph.getNeighbors(nodeID);
                for (int j = 0; j < neighbors.size(); ++j) {
                    int neighborID = neighbors[j].to;
                    Vector2 pos2 = positions.get(neighborID);
                    
                    Vector2 delta = pos2 - pos1;
                    float distance = delta.magnitude();
                    
                    // Only apply attraction if nodes are not too close
                    if (distance > 1.0f) {
                        // Spring force proportional to distance
                        Vector2 force = delta * (attractionStrength * distance / distance); // normalized
                        forces.put(nodeID, forces.get(nodeID) + force);
                    }
                }
            }
            
            // Update velocities and positions using Verlet integration
            for (int i = 0; i < allNodes.size(); ++i) {
                int nodeID = allNodes[i];
                
                Vector2 force = forces.get(nodeID);
                Vector2 velocity = velocities.get(nodeID);
                
                // Update velocity with damping
                velocity = velocity * damping + force * 0.01f; // Scale force
                
                // Limit maximum velocity to prevent instability
                float velMag = velocity.magnitude();
                const float maxVelocity = 20.0f;
                if (velMag > maxVelocity) {
                    velocity = velocity * (maxVelocity / velMag);
                }
                
                velocities.put(nodeID, velocity);
                
                // Update position
                Vector2 pos = positions.get(nodeID);
                pos = pos + velocity;
                positions.put(nodeID, pos);
            }
        }
        
        return positions;
    }
    
    // Calculate bounding box of layout
    static void getBoundingBox(const HashMap<int, Vector2>& positions,
                              float& minX, float& minY, float& maxX, float& maxY) {
        minX = minY = 1e9f;
        maxX = maxY = -1e9f;
        
        DynamicArray<int> allKeys = positions.keys();
        for (int i = 0; i < allKeys.size(); ++i) {
            Vector2 pos = positions.get(allKeys.get(i));
            
            if (pos.x < minX) minX = pos.x;
            if (pos.x > maxX) maxX = pos.x;
            if (pos.y < minY) minY = pos.y;
            if (pos.y > maxY) maxY = pos.y;
        }
    }
    
    // Center layout at origin
    static void centerLayout(HashMap<int, Vector2>& positions) {
        float minX, minY, maxX, maxY;
        getBoundingBox(positions, minX, minY, maxX, maxY);
        
        float centerX = (minX + maxX) / 2.0f;
        float centerY = (minY + maxY) / 2.0f;
        
        DynamicArray<int> allKeys = positions.keys();
        for (int i = 0; i < allKeys.size(); ++i) {
            int key = allKeys.get(i);
            Vector2 pos = positions.get(key);
            positions.put(key, Vector2(pos.x - centerX, pos.y - centerY));
        }
    }
};

#endif // GRAPHLAYOUT_H