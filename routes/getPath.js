import {Router} from "express";
import { execFile } from "node:child_process";
// import db from "../database/database.js";
import util from "util";
const execFilePromise = util.promisify(execFile);


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

// Connect to the database
pool.connect((err, client, release) => {
  if (err) {
    return console.error("Error acquiring client", err.stack);
  }
  console.log("Database connected successfully");
  release(); // Release the client back to the pool
});
const db=pool;
const router = Router();

async function getlocationsarray(dataset) {
  const responseArray = [];
  let serial = 1;
  for (let item of dataset) {
    item = String(item);
    const query = `SELECT lat,long FROM stationlist WHERE stationname LIKE $1`;
    const values = [item + "%"];
    const result = await db.query(query, values);
    if (result.rows.length > 0) {
      const lat = Number(result.rows[0].lat);
      const lng = Number(result.rows[0].long);
      responseArray.push({
        key: serial.toString(),
        location: { lat, lng },
        name: item,
      });
      serial++;
    }
  }
  return responseArray;
}

router.post("/getpath", async (req, res) => {
  const from = req.body.from;
  const to = req.body.to;

  try {
    const { stdout } = await execFilePromise("./pathfinder.exe", [from, to]);
    const dataset = stdout
      .split(/\r?\n/)
      .map((name) => name.trim())
      .filter((name) => name !== "");
    const responseArray = await getlocationsarray(dataset);
    res.json(responseArray);
  } catch (error) {
    console.error("Error executing pathfinder:", error);
    res.status(500).json({ error: "Internal Server Error" });
  }
});

export default router;
