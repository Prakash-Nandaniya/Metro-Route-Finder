import React, { useState, useEffect } from "react";

function TO() {
  const [inputValue, setinputValue] = useState("");
  const [suggestions, setsuggestions] = useState([]);

  useEffect(() => {
    if (inputValue) {
      fetch(`http://localhost:3000/suggest?input=${inputValue}`)
        .then(response => response.json())
        .then(data => setsuggestions(data))
        .catch(error => console.error('Error fetching suggestions:', error));
    } else {
      setsuggestions([]);
    }
  }, [inputValue]);

  return (
    <div className="form-group">
      <label htmlFor="exampleInputEmail1">TO</label>
      <input
      name="to"
        type="text"
        className="form-control"
        id="exampleInputEmail2"
        aria-describedby="emailHelp"
        placeholder="Enter drop location"
        // value={inputValue}
        onChange={(e) => setinputValue(e.target.value)}
      />
      {suggestions.length > 0 && (
        <div className="suggestions">
          {suggestions.map((suggestion, index) => (
            <div
              className="option"
              key={index}
              onClick={() => {setinputValue(suggestion+'*');
                document.getElementById('exampleInputEmail2').value=suggestion;
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

export default TO;
