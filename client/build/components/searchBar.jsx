import React,{useContext} from "react";
import From from "./from";
import To from "./to";
import Pointscontext from './pointscontext';

function SB() {
  const a= useContext(Pointscontext);
  const handleSubmit = async (event) => {
    event.preventDefault(); // Prevent default form submission
    
    // Assuming From and To components have inputs with refs or IDs to collect their values
    // This is a placeholder for how you might collect form data
    const formData = {
      from: document.getElementById('exampleInputEmail1').value,
      to: document.getElementById('exampleInputEmail2').value,
    };
    
    try {
      const response = await fetch('/getpath', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(formData),
      });

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const data = await response.json();
      if(data.length==0){
        alert("No route found");
      }
      // console.log(data.type);
      a.update(data);
      // Handle the response data
    } catch (error) {
      console.error('Error submitting form:', error);
    }
  };

  return (
    <form onSubmit={handleSubmit}>
      <From/>
      <To/>
      <button type="submit" class="btn btn-primary">Find route</button>
    </form>
  );
}

export default SB;