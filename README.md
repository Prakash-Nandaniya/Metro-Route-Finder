# Delhi Metro Route Finder

This project is a Delhi Metro route finder application that helps users find the best route between specified pickup and drop locations with minimum cost. The application displays the route on a google map, showing every station between the pickup and drop  locations and show station name on hovering over markers on map.During station name searching suggestions are given based on entered latters.

## Overview
- **Frontend**: Built with React and utilizes Google Maps API to display route locations with Advanced Markers.
- **Backend**: Implemented using Node.js and Express to handle route processing and serve API requests.
- **Database**: PostgreSQL is used to store the station dataset, managed through pgAdmin and hosted on Render.

## Frontend
The frontend of the application is developed using React. It leverages the Google Maps API to plot the metro route and uses the Advanced Marker feature to show station names on hover. A search bar with a suggestion feature helps users easily find station names based on the letters they enter.

### Key Features
- **Route Display**: Shows the best route on the map from pickup to drop location.
- **Advanced Markers**: Displays station names on hover.{ pickup loaction(green), drop location(red), inbetween(blue) }
- **Station Suggestions**: Provides station name suggestions in the search bar for easier input.


