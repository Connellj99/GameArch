/*
A class to hold all the GraphicsBuffers in the game (except the backbuffer which should still reside in the
GraphicsSystem – although having a way of getting to it through the GraphicsBufferManager is not a bad
idea)
Data
• A “map” of GraphicsBuffers
Functions
• Constructor/destructor
• Some way of adding/deleting/getting GraphicsBuffers
• Clear -remove and delete all GraphicsBuffers (not including the BackBuffer – GraphicsSystem
should still clean that up itself)
*/