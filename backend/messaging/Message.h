#pragma once
#include <string>
#include <crow/json.h>
using namespace crow;
using namespace std;
struct Message {
    string id;
    string senderId;
    string receiverId;
    string content;
    long long timestamp;
    bool delivered = false;
    bool read = false;

    // Convert Message → JSON
    json::wvalue toJson() const {
        json::wvalue x;
        x["id"] = id;
        x["senderId"] = senderId;
        x["receiverId"] = receiverId;
        x["content"] = content;
        x["timestamp"] = timestamp;
        x["delivered"] = delivered;
        x["read"] = read;
        return x;
    }

    // Convert JSON → Message
    static Message fromJson(const crow::json::rvalue& x) {
        Message m;
        m.id = x["id"].s();
        m.senderId = x["senderId"].s();
        m.receiverId = x["receiverId"].s();
        m.content = x["content"].s();
        m.timestamp = x["timestamp"].i();
        m.delivered = x["delivered"].b();
        m.read = x["read"].b();
        return m;
    }
};
