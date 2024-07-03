import React,{useState} from "react";
import Searchbar from "./components/searchBar";
import MapComponent from "./components/map.tsx";
import Pointstate from "./components/pointsstate.js";

function App() {
  // State to hold the selected suggestion
const [selectedSuggestion, setSelectedSuggestion] = useState(null);

// Callback function to update the selected suggestion
const handleSelectSuggestion = (suggestion) => {
  setSelectedSuggestion(suggestion);
};

// Pass handleSelectSuggestion and selectedSuggestion as props to from.jsx and map.tsx
  return (
    <div>
      <Pointstate>
      <Searchbar handleSelectSuggestion={handleSelectSuggestion}/>
      <MapComponent selectedSuggestion={selectedSuggestion}
        googleMapsApiKey="AIzaSyBAwjIZZETmOVbucepaPuAiGyOgy4wfSao"
      />
      </Pointstate>
    </div>
  );
}

export default App;
