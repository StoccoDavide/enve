%
% File: Track3D.m
%
classdef Track3D < handle
  % A class for implementing a MATLAB Graphics visualization of a
  % 3D Track, given a 3D mesh 
  %
  properties (SetAccess=private)
      
  end
  %
  % Public methods
  methods
    function obj = Track3D(Nodes,Elements,MU)
      obj.createGeometry(Nodes,Elements,MU);
    end
    %
    function r = isAlive(obj)
    % Call this to check whether the figure window is still alive.
      r = isvalid(obj) ;
    end
  end
  %
  % Private methods
  methods (Access=private)
    
    function createGeometry(~,Nodes,Elements,MU)
    % Creates all of the graphics objects for the visualization.
    % color_map
    MU_min=min(min(MU),0.2);
    col=[0.6 0.6 0.6]-[(1-MU)/(1-MU_min) (1-MU)/(1-MU_min) (1-MU)/(1-MU_min)].*[0.6 0.2 0.4];
    %figure
    hold on
    patch('Vertices',Nodes,'Faces',Elements,'FaceVertexCData',col,'FaceColor','flat','FaceAlpha',0.5,'FaceLighting', 'gouraud')
    end
  end
end
