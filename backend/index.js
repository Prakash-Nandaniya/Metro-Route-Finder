import express from "express";
import bodyParser from "body-parser";
import pg from "pg";
import { execFile } from "node:child_process";

import util from "util";
const execFilePromise = util.promisify(execFile);

const app = express();
const port = process.env.PORT;
const db = new pg.Client({
   user: "postgres",
  host: "prakashn362650.ddnsking.com", // Replace with your actual No-IP hostname
  database: "metrodata",
  password: "prakashn@03",
  port: 5432,
});
db.connect();

async function getSuggestionsForInput(input) {
  const query = `SELECT stationname FROM stationlist WHERE stationname LIKE $1`;
  const values = [input + "%"]; // Assuming 'input' is the string to match

  try {
    const res = await db.query(query, values);
    const ans = [];
    for (const i of res.rows) {
      ans.push(i.stationname);
    }
    return ans; // Returns an array of matching rows
  } catch (err) {
    console.error(err);
    return [];
  }
}

/**
 * @typedef {Object} Poi
 * @property {string} key
 * @property {google.maps.LatLngLiteral} location
 * @property {string} name
 */

/**
 * Gets an array of locations.
 * @param {Array} dataset - The dataset to process.
 * @returns {Promise<Poi[]>} - A promise that resolves to an array of Poi objects.
 */
async function getlocationsarray(dataset) {
  /** @type {Poi[]} */
  const responseArray = [];
  let serial = 1; // Initialize serial number
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
      serial++; // Increment serial number for each item
    }
  }
  return responseArray;
}

app.use(express.static("client/build"));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.json());

app.get("/", (req, res) => {
  res.sendFile("../client/build/index.html");
});

app.get("/suggest", async (req, res) => {
  const input = req.query.input; // Access the input query parameter
  if (input[-1] == "*") {
    return res.json([]);
  }
  const suggestions = await getSuggestionsForInput(input); 
  if(suggestions[0]==input){
    return res.json([]);
  }
 return res.json(suggestions);
});

app.post("/getpath", async (req, res) => {
  const from = req.body.from;
  const to = req.body.to;

  try {
    const { stdout } = await execFilePromise("./pathfinder.exe", [from, to]);
    const dataset = stdout.split(/\r?\n/).map(name => name.trim()).filter(name => name !== "");
    const responseArray = await getlocationsarray(dataset);
    res.json(responseArray); // Send the response back to the client
  } catch (error) {
    console.error("Error executing pathfinder:", error);
    res.status(500).json({ error: "Internal Server Error" });
  }
});

// app.post("/getpath", async (req, res) => {
//   const from = req.body.from;
//   const to=req.body.to;
//   const dataset;

//   const child = await execFile(
//     "./pathfinder.exe",
//     [from, to],
//     (error, stdout, stderr) => {
//       if (error) {
//         throw error;
//       }
//       console.log(stdout);
//       console.log("hello");
//       dataset = stdout.split("\n").filter((name) => name.trim() !== "");

//     }
//   );
//   const responseArray = [];
//   const serial = 1; // Initialize serial number

//   for (const item of dataset) {
//     const { lat, lng } = await db.query(`SELECT lat long FROM stationlist WHERE stationname = $1`,[item]);
//     responseArray.push({
//       key: serial.toString(),
//       location: { lat, lng },
//     });

//     serial++; // Increment serial number for each item
//   }
//   res.json(responseArray);
// });

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
