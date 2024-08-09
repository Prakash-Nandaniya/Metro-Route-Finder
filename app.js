import express from "express";
import bodyParser from "body-parser";

import getpath from "./routes/getPath.js";
import suggest from "./routes/suggest.js";


const app = express();
const port = 3000;


app.use(express.static("client/build"));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.json());

//handeling routes
app.use(getpath);
app.use(suggest);


app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
