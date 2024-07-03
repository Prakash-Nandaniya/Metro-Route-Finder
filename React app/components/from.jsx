import React, { useState, useEffect } from "react";

function From(props) {
  const [inputValue, setInputValue] = useState("");
  const [suggestions, setSuggestions] = useState([]);

  useEffect(() => {
    if (inputValue) {
      fetch(`https://metroproject-1.onrender.com/suggest?input=${inputValue}`)
        .then(response => response.json())
        .then(data => setSuggestions(data))
        .catch(error => console.error('Error fetching suggestions:', error));
    } else {
      setSuggestions([]);
    }
  }, [inputValue]);

  return (
    <div className="searchboxContainer">
        <div className="searchbar">
      <label htmlFor="exampleInputEmail1">From</label>
      <input
      name="from"
        type="text"
        className="form-control"
        id="exampleInputEmail1"
        aria-describedby="emailHelp"
        placeholder="Enter pickup location"
        // value={inputValue}
        onChange={(e) => setInputValue(e.target.value)}
      />
      </div>
      {suggestions.length > 0 && (
        <div className="suggestions">
          {suggestions.map((suggestion, index) => (
            <div
              className="option"
              key={index}
              onClick={() => {setInputValue(suggestion+'*');
                document.getElementById('exampleInputEmail1').value=suggestion;
              }
              }
            >
              {suggestion}
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

export default From;
