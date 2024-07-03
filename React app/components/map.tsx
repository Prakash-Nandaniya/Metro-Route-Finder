import React,{useContext} from 'react';
import Pointscontext from './pointscontext';

import {
    APIProvider,
    Map,
    AdvancedMarker,
    MapCameraChangedEvent,
    Pin
  } from '@vis.gl/react-google-maps';
  import { Polyline } from '@react-google-maps/api'; // Adjust import based on your mapping library


function Mapcomponent(){
  const { state } = useContext(Pointscontext); // Access state using useContext

  // Determine the default center from the first point in the state array
  const defaultCenter = state.length > 0 ? { lat: state[Math.floor(state.length / 2)].lat, lng: state[Math.floor(state.length / 2)].lng } : { lat: 28.681500, lng: 77.222800 };
  return (
    <div className='mapcomponent'>
  <APIProvider apiKey={'AIzaSyBAwjIZZETmOVbucepaPuAiGyOgy4wfSao'} onLoad={() => console.log('Maps API has loaded.')}>
   <Map
    defaultZoom={12}
    defaultCenter={ defaultCenter }
    mapId='DEMO_MAP_ID'
    onCameraChanged={ (ev: MapCameraChangedEvent) =>
        console.log('camera changed:', ev.detail.center, 'zoom:', ev.detail.zoom)
    }>
        <PoiMarkers />
</Map>
 </APIProvider>
 </div>); 
}

const PoiMarkers = () => {
  const { state } = useContext(Pointscontext);

  const getColor = (index) => {
    if (index === state.length-1) return '#00FF00'; // Green for the first marker
    if (index === 0) return '#FF0000'; // Red for the last marker
    return '#0000FF'; // Blue for all other markers
  };

  const path = state.map(({ location }) => location); // Assuming location is in the format { lat: number, lng: number }

  return (
    <>
      {state.map(({ key, location, name }, index) => (
        <AdvancedMarker
          key={key}
          position={location}
          
          title={name} // Assuming you want to display the name on hover
        >
          <div style={{ position: 'absolute', bottom: '100%', whiteSpace: 'nowrap', backgroundColor: 'white', padding: '2px' ,color:"black"}}>
    {name}
  </div>
          <Pin background={getColor(index)} glyphColor={'#000'} borderColor={'#000'} />
        </AdvancedMarker>
      ))}
      <Polyline
        path={path}
        options={{
          strokeColor: '#0000FF',
          strokeOpacity: 0.8,
          strokeWeight: 2,
          // fillColor: '#0000FF',
          // fillOpacity: 0.35,
          clickable: false,
          draggable: false,
          editable: false,
          visible: true,
          // radius: 30000,
          zIndex: 1,
        }}
      />
    </>
  );
};


export default Mapcomponent;
