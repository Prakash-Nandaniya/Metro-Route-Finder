import { Router } from "express";
// import db from "../database/database";

const router = Router();

import pkg from "pg";
const { Pool } = pkg;

// Create a new pool instance
const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "postgres",
  password: "prakashn@03",
  port: 5432,
});
const db=pool;
// Connect to the database
pool.connect((err, client, release) => {
  if (err) {
    return console.error("Error acquiring client", err.stack);
  }
  console.log("Database connected successfully");
  release(); // Release the client back to the pool
});


async function getSuggestionsForInput(input) {
  const query = `SELECT stationname FROM stationlist WHERE stationname LIKE $1`;
  const values = [input + "%"];

  try {
    const res = await db.query(query, values);
    const ans = [];
    for (const i of res.rows) {
      ans.push(i.stationname);
    }
    return ans;
  } catch (err) {
    console.error(err);
    return [];
  }
}

router.get("/suggest", async (req, res) => {
  const x = req.query.input;
  const input = x[0].toUpperCase() + x.substring(1);
  if (input[-1] == "*") {
    return res.json([]);
  }
  const suggestions = await getSuggestionsForInput(input);
  if (suggestions[0] == input) {
    return res.json([]);
  }
  return res.json(suggestions);
});

export default  router;
