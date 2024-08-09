import { Pool } from "pg";

// Create a new pool instance
const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "postgres",
  password: "prakashn@03",
  port: 5432,
});

// Connect to the database
pool.connect((err, client, release) => {
  if (err) {
    return console.error("Error acquiring client", err.stack);
  }
  console.log("Database connected successfully");
  release(); // Release the client back to the pool
});

export default pool;
