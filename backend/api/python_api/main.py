from fastapi import FastAPI, HTTPException, status
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import requests
from typing import Optional, List

app = FastAPI(title="Social Graph Explorer API", version="1.0.0")

# CORS middleware for React frontend
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # In production, specify your React app URL
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# C++ Backend URL
CPP_BACKEND = "http://localhost:8080"

# ==================== Models ====================

class UserRegister(BaseModel):
    username: str
    password: str

class UserLogin(BaseModel):
    username: str
    password: str

class PostCreate(BaseModel):
    content: str

# ==================== Health Check ====================

@app.get("/")
def root():
    return {"message": "Social Graph Explorer Python API", "status": "running"}

@app.get("/health")
def health_check():
    try:
        response = requests.get(f"{CPP_BACKEND}/", timeout=2)
        cpp_status = "running" if response.status_code == 200 else "error"
    except:
        cpp_status = "offline"
    
    return {
        "python_api": "running",
        "cpp_backend": cpp_status
    }

# ==================== User Routes ====================

@app.post("/api/users/register", status_code=status.HTTP_201_CREATED)
def register_user(user: UserRegister):
    """Register a new user"""
    try:
        response = requests.post(
            f"{CPP_BACKEND}/api/users/register",
            json={"username": user.username, "password": user.password},
            headers={"Content-Type": "application/json"}
        )
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=400, detail=data.get("error", "Registration failed"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.post("/api/users/login")
def login_user(user: UserLogin):
    """Login user"""
    try:
        response = requests.post(
            f"{CPP_BACKEND}/api/users/login",
            json={"username": user.username, "password": user.password},
            headers={"Content-Type": "application/json"}
        )
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=401, detail=data.get("error", "Invalid credentials"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.get("/api/users/search")
def search_users(prefix: str = ""):
    """Search users by username prefix"""
    try:
        response = requests.get(f"{CPP_BACKEND}/api/users/search?prefix={prefix}")
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=400, detail=data.get("error", "Search failed"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.get("/api/users/{user_id}")
def get_user(user_id: int):
    """Get user details by ID"""
    try:
        response = requests.get(f"{CPP_BACKEND}/api/users/{user_id}")
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=404, detail=data.get("error", "User not found"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.delete("/api/users/{user_id}")
def delete_user(user_id: int):
    """Delete user by ID"""
    try:
        response = requests.delete(f"{CPP_BACKEND}/api/users/{user_id}")
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=404, detail=data.get("error", "User not found"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

# ==================== Post Routes ====================

@app.post("/api/users/{user_id}/posts", status_code=status.HTTP_201_CREATED)
def create_post(user_id: int, post: PostCreate):
    """Create a new post for user"""
    try:
        response = requests.post(
            f"{CPP_BACKEND}/api/users/{user_id}/posts",
            json={"content": post.content},
            headers={"Content-Type": "application/json"}
        )
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=400, detail=data.get("error", "Failed to create post"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.get("/api/users/{user_id}/posts")
def get_user_posts(user_id: int):
    """Get all posts for a user"""
    try:
        response = requests.get(f"{CPP_BACKEND}/api/users/{user_id}/posts")
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=404, detail=data.get("error", "User not found"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

@app.delete("/api/users/{user_id}/posts/{post_index}")
def delete_post(user_id: int, post_index: int):
    """Delete a specific post"""
    try:
        response = requests.delete(f"{CPP_BACKEND}/api/users/{user_id}/posts/{post_index}")
        data = response.json()
        
        if not data.get("success"):
            raise HTTPException(status_code=404, detail=data.get("error", "Post not found"))
        
        return data
    except requests.exceptions.RequestException as e:
        raise HTTPException(status_code=503, detail="Backend service unavailable")

# ==================== Run Server ====================

if __name__ == "__main__":
    import uvicorn
    print("="*50)
    print("Social Graph Explorer - Python API Layer")
    print("="*50)
    print("Python API: http://localhost:5000")
    print("API Docs: http://localhost:5000/docs")
    print("C++ Backend: http://localhost:8080")
    print("="*50)
    uvicorn.run(app, host="0.0.0.0", port=5000)
