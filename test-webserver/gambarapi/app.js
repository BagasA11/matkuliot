const express = require("express");
const path = require("path");
const cors = require("cors");
const app = express();

const PORT = 8080;

// Path folder gambar
const imageDir = path.join(__dirname, "images");

// Melayani file statis (gambar)
app.use(cors());
app.use("/images", express.static(imageDir));
// app.use("/images", express.static("/"));

// Route dasar untuk tes server
app.get("/", (req, res) => {
    res.send("Server gambar berjalan. Akses gambar via /images/nama_file.jpg");
});
console.log("Serving images from:", imageDir);

// Jalankan server
app.listen(PORT, () => {
    console.log(`Server berjalan di http://localhost:${PORT}`);
});
