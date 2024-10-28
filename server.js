const express = require('express');
const app = express();
const port = 3000;

// Endpoint to receive GPS data
app.get('/update-location', (req, res) => {
  const latitude = req.query.lat;
  const longitude = req.query.lng;

  if (latitude && longitude) {
    console.log(`Received GPS Data - Latitude: ${latitude}, Longitude: ${longitude}`);
    res.status(200).send('GPS Data Received');
    // Here, you can save data to a database or a file for later use
  } else {
    res.status(400).send('Invalid GPS Data');
  }
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
