export const dummyUsers = [
  {
    id: 1,
    name: "Alice Chen",
    avatar: "AC",
    bio: "Software engineer passionate about graph algorithms and distributed systems.",
    followers: 1243,
    following: 432,
    posts: 87,
    connections: [2, 3, 5],
    joinedDate: "2023-01-15"
  },
  {
    id: 2,
    name: "Bob Martinez",
    avatar: "BM",
    bio: "Data scientist exploring social network analysis and machine learning.",
    followers: 892,
    following: 567,
    posts: 134,
    connections: [1, 4, 6, 7],
    joinedDate: "2023-03-22"
  },
  {
    id: 3,
    name: "Carol Zhang",
    avatar: "CZ",
    bio: "Algorithm enthusiast. Love solving complex problems.",
    followers: 2156,
    following: 234,
    posts: 203,
    connections: [1, 4, 5, 8],
    joinedDate: "2022-11-08"
  },
  {
    id: 4,
    name: "David Kumar",
    avatar: "DK",
    bio: "Building the future of social graphs. CS researcher.",
    followers: 3421,
    following: 891,
    posts: 412,
    connections: [2, 3, 6, 9],
    joinedDate: "2022-08-14"
  },
  {
    id: 5,
    name: "Emma Wilson",
    avatar: "EW",
    bio: "Graph theory researcher and open source contributor.",
    followers: 1876,
    following: 654,
    posts: 156,
    connections: [1, 3, 7, 10],
    joinedDate: "2023-02-19"
  },
  {
    id: 6,
    name: "Frank Thompson",
    avatar: "FT",
    bio: "Full stack developer interested in network visualization.",
    followers: 945,
    following: 423,
    posts: 98,
    connections: [2, 4, 8],
    joinedDate: "2023-04-30"
  },
  {
    id: 7,
    name: "Grace Lee",
    avatar: "GL",
    bio: "AI researcher exploring social dynamics through data.",
    followers: 2789,
    following: 512,
    posts: 267,
    connections: [2, 5, 9],
    joinedDate: "2022-10-05"
  },
  {
    id: 8,
    name: "Henry Park",
    avatar: "HP",
    bio: "Backend engineer focused on scalable graph databases.",
    followers: 1532,
    following: 378,
    posts: 145,
    connections: [3, 6, 10],
    joinedDate: "2023-01-28"
  },
  {
    id: 9,
    name: "Iris Rodriguez",
    avatar: "IR",
    bio: "Product manager with a passion for network effects.",
    followers: 1234,
    following: 789,
    posts: 112,
    connections: [4, 7],
    joinedDate: "2023-05-12"
  },
  {
    id: 10,
    name: "Jack Foster",
    avatar: "JF",
    bio: "Graph algorithms and optimization enthusiast.",
    followers: 687,
    following: 234,
    posts: 76,
    connections: [5, 8],
    joinedDate: "2023-06-07"
  }
];

export const getUserById = (id) => {
  return dummyUsers.find(user => user.id === id);
};

export const getUserConnections = (userId) => {
  const user = getUserById(userId);
  if (!user) return [];
  return user.connections.map(connId => getUserById(connId)).filter(Boolean);
};
