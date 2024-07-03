# Delhi Metro Route Finder

This project is a Delhi Metro route finder application that helps users find the best route between specified pickup and drop locations with minimum cost. The application displays the route on a Google map, showing every station between the pickup and drop locations and station names when hovering over markers on the map. During station name searching, suggestions are provided based on entered letters.

## Overview
- **Frontend**: Built with React and utilizes Google Maps API to display route locations with Advanced Markers.
- **Backend**: Implemented using Node.js and Express to handle route processing and serve API requests.
- **Database**: PostgreSQL is used to store the station dataset, managed through pgAdmin and hosted on Render.

## Frontend
The frontend of the application is developed using React. It leverages the Google Maps API to plot the metro route and uses the Advanced Marker feature to show station names on hover. A search bar with a suggestion feature helps users easily find station names based on the letters they enter.

### Key Features
- **Route Display**: Shows the best route on the map from pickup to drop location.
- **Advanced Markers**: Displays station names on hover with different colors for different types of stations:
  - Pickup location (green)
  - Drop location (red)
  - Intermediate stations (blue)
- **Station Suggestions**: Provides station name suggestions in the search bar for easier input.

## Backend
The backend is developed using Node.js and Express. It uses the Google Maps API to display route stations on the map with markers and finds the best route with minimum cost using a `pathfinder.cpp` file that implements graph concepts to map the entire Delhi Metro network.

### Technologies Used
- **Node.js**
- **Express**
- **Google Maps API**

### Key Features
- **API Endpoints**: Handles route calculation and station data retrieval.
- **Route Processing**: Determines the best route between specified metro stations using the `pathfinder.cpp` file, which takes both location names and returns the best route.
- **Station Name Suggestions**: Uses event listeners in React components, sending requests for suggestions to the backend as each letter is entered.
- **Google Maps Integration**: Uses Google Maps API to fetch and display route details.

## Database
A remote PostgreSQL database is used, hosted on Render, and managed locally by connecting to pgAdmin.

## pathfinder.cpp
This file is the heart of the project, responsible for finding the best route with minimum cost for given pickup and drop locations. It reads all color line station files and makes a linked list of lines, with each node representing a station. By doing this, it maps the entire network of the Delhi Metro. At each station, the metro can go in both directions, and based on this condition, it finds the best route for the journey by evaluating all possible routes, sorting them based on total fare, and returning the route with the minimum fare.

## Authors
- Prakash Nandaniya
- Kumar Ashish Aditya
