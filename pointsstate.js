import pointscontext from "./pointscontext";
import React,{useState} from 'react';

const Pointstate=(props)=>{
    const [state,setstate]= useState([]);
    const update=(data)=>{
        setstate(data);
    }
    return(
        <pointscontext.Provider value={{state,update}}>
            {props.children}
        </pointscontext.Provider>
    )
}


export default Pointstate;