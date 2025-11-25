# Python API Layer

This is the FastAPI layer that sits between the React frontend and C++ backend.

## Setup
```bash
pip install -r requirements.txt
```

## Run

Make sure the C++ backend is running first, then:
```bash
python main.py
```

Server will start on http://localhost:5000

## API Documentation

- Swagger UI: http://localhost:5000/docs
- ReDoc: http://localhost:5000/redoc

## Architecture
```
React (port 3000) → Python FastAPI (port 5000) → C++ Backend (port 8080)
```
