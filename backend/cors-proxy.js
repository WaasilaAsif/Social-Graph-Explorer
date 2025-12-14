// Simple CORS proxy for development
// This forwards requests to the C++ backend and adds CORS headers

const http = require('http');
const https = require('https');

const TARGET_HOST = 'localhost';
const TARGET_PORT = 8081;
const PROXY_PORT = 8082;

const server = http.createServer((clientReq, clientRes) => {
  console.log(`${clientReq.method} ${clientReq.url}`);

  // Handle OPTIONS preflight
  if (clientReq.method === 'OPTIONS') {
    clientRes.writeHead(204, {
      'Access-Control-Allow-Origin': '*',
      'Access-Control-Allow-Methods': 'GET, POST, PUT, DELETE, OPTIONS',
      'Access-Control-Allow-Headers': 'Content-Type',
      'Access-Control-Max-Age': '86400',
    });
    clientRes.end();
    return;
  }

  // Proxy the request
  const options = {
    hostname: TARGET_HOST,
    port: TARGET_PORT,
    path: clientReq.url,
    method: clientReq.method,
    headers: clientReq.headers,
  };

  const proxyReq = http.request(options, (proxyRes) => {
    // Copy headers from backend response
    const headers = { ...proxyRes.headers };
    
    // Only add CORS headers if they don't already exist
    if (!headers['access-control-allow-origin']) {
      headers['Access-Control-Allow-Origin'] = '*';
      headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS';
      headers['Access-Control-Allow-Headers'] = 'Content-Type';
    }

    clientRes.writeHead(proxyRes.statusCode, headers);
    proxyRes.pipe(clientRes);
  });

  proxyReq.on('error', (err) => {
    console.error('Proxy error:', err.message);
    clientRes.writeHead(502, {
      'Content-Type': 'application/json',
      'Access-Control-Allow-Origin': '*',
    });
    clientRes.end(JSON.stringify({
      success: false,
      error: 'Backend server not available',
      message: err.message
    }));
  });

  clientReq.pipe(proxyReq);
});

server.listen(PROXY_PORT, () => {
  console.log(`\n${'='.repeat(50)}`);
  console.log(`CORS Proxy Server Running`);
  console.log(`Listening on: http://localhost:${PROXY_PORT}`);
  console.log(`Forwarding to: http://localhost:${TARGET_PORT}`);
  console.log(`${'='.repeat(50)}\n`);
  console.log(`Update your frontend to use: http://localhost:${PROXY_PORT}`);
  console.log(`Make sure backend server is running on port ${TARGET_PORT}\n`);
});
