%
% File: TestRig_graphic.m
%
classdef TestRig_graphic < handle
    % A class for implementing a MATLAB Graphics visualization of the Tire
    % Test Rig
    
    properties (SetAccess=private)
        rig_up;
        rig_low;
        wheel;
        Rig_up         = gobjects(1,1);
        Rig_low        = gobjects(1,1);
        Wheel          = gobjects(1,1);
        Trace_wheel    = gobjects(1,1);
        en_trace_wheel = 1;
        RF_up_rig      = eye(4);
        RF_low_rig     = eye(4);
        RF_wheel       = eye(4);
        RF_cam         = eye(4) +[zeros(4,3) [ones(3,1) ; 0]];
    end
    
    %% Public methods
    methods
        function obj = TestRig_graphic(rig_up_stl,rig_up_stl_scale,rig_low_stl,rig_low_stl_scaale,wheel_stl,wheel_stl_scale,en_trace_wheel, RF_up_rig, RF_low_rig, RF_wheel, RF_cam, varargin )
            % varargin{1} wheel radius
            % varargin{2} wheel width
            
            % setup graphics
            ax = gca;                               % get current graphic axis
            view(3);
            transf = hgtransform('Parent', ax);     % create transforms
            
            % Create Bodies objects
            obj.Rig_up(1)   = hgtransform('Parent', transf);
            createObj(obj, rig_up_stl,obj.Rig_up(1),'red',0.8,rig_up_stl_scale);
            
            obj.Rig_low(1) = hgtransform('Parent', transf);
            createObj(obj, rig_low_stl,obj.Rig_low(1),'yellow',0.8,rig_low_stl_scaale);
            
            obj.Wheel(1) = hgtransform('Parent', transf);
            if size(varargin) ~= 0
                createWheel(obj, wheel_stl,1,obj.Wheel(1),'black',0.5,wheel_stl_scale,varargin{1},varargin{2});
            else
                createWheel(obj, wheel_stl,1,obj.Wheel(1),'black',0.5,wheel_stl_scale);
            end
            
            % Create the traces
            obj.en_trace_wheel = en_trace_wheel;
            if obj.en_trace_wheel
                obj.Trace_wheel(1) = animatedline('Parent', ax, 'MaximumNumPoints', 80, 'Color', [0 0.4470 0.7410], 'LineWidth',2);
            end
            
            % graphics setup pt2 (cannot be moved on top!)
            ax.DataAspectRatio = [1 1 1];           % fix axpect ratio
            grid(ax,'on');                          % grid
            light                                   % create a light
            lighting gouraud
            material dull                           % material property
            campos(obj.RF_cam(1:3,4));              % camera position
            camtarget(obj.RF_wheel(1:3,4));         % camera target
            camva(60);                              % camera FOV
            camproj perspective
            
            % Update graphic objects.
            obj.RF_up_rig  = RF_up_rig;
            obj.RF_low_rig = RF_low_rig;
            obj.RF_wheel   = RF_wheel;
            obj.RF_cam     = RF_cam;
            
            % first graphic update
            obj.updateTransforms();
            
        end
        
        function step(obj, RF_up_rig, RF_low_rig, RF_wheel, RF_cam )
            % Update graphic objects.
            obj.RF_up_rig  = RF_up_rig;
            obj.RF_low_rig = RF_low_rig;
            obj.RF_wheel   = RF_wheel;
            obj.RF_cam     = RF_cam;
            
            % update objects positions
            obj.updateTransforms();
            
            % update traces
            if obj.en_trace_wheel
                obj.Trace_wheel.addpoints(RF_wheel(1,4),RF_wheel(2,4),RF_wheel(3,4));
            end
            
        end
        
        function clearTraces(obj)
            % Call this to clear the traces.
            obj.Trace_wheel.clearpoints();
        end
        
        function destroy(obj)
            % Call this to clear the figure 
            delete(obj.Rig_up(1));
            delete(obj.Rig_low(1));
            delete(obj.Wheel(1));
            delete(obj.Trace_wheel(1));
            drawnow
        end
        
        function r = isAlive(obj)
            % Call this to check whether the figure window is still alive.
            r = isvalid(obj)            && ...
                isvalid(obj.Rig_up(1))  && ...
                isvalid(obj.Rig_low(1)) && ...
                isvalid(obj.Wheel(1));
        end
        
    end
    
    
    %% Private methods
    methods (Access=private)
        
        function createObj(~, stl_obj,parent,color,transparency,scale)
            % Creates the geometry
            % Assign patches
            temp_obj   = stlread(stl_obj);
            
            %scale patches
            temp_obj  = triangulation( temp_obj.ConnectivityList, scale.*temp_obj.Points);
            
            % create body object: rear right
            trisurf(temp_obj,                   ...
                'EdgeColor',    'none',         ...
                'FaceColor',     color,         ...
                'FaceLighting', 'gouraud',      ...
                'FaceAlpha',     transparency,  ...
                'Parent',        parent);
        end
        
        function createWheel(~, stl_wheel,mir,parent,color,transparency,scale,varargin)
            % Creates the geometry
            % Assign patches
            temp_wheel   = stlread(stl_wheel);
            
            if size(varargin) ~= 0
                R = varargin{1};
                B = varargin{2};
                R_cad = (max(temp_wheel.Points(:,1))-min(temp_wheel.Points(:,1)))/2*scale;
                B_cad = (max(temp_wheel.Points(:,2))-min(temp_wheel.Points(:,2)))/2*scale;
                cad_scale_y = B/B_cad;
                cad_scale_xz = R/R_cad;
            else
                cad_scale_y = 1;
                cad_scale_xz = 1;
            end
            
            temp_wheel_p = [cad_scale_xz*temp_wheel.Points(:,1) cad_scale_y*mir*temp_wheel.Points(:,2) cad_scale_xz*temp_wheel.Points(:,3)];
            temp_wheel = triangulation( temp_wheel.ConnectivityList,scale.*temp_wheel_p );
            
            % create wheel object: rear right
            trisurf(temp_wheel,                ...
                'EdgeColor',    'none',        ...
                'FaceColor',     color,        ...
                'FaceLighting', 'gouraud',     ...
                'FaceAlpha',     transparency, ...
                'Parent',        parent);
        end
        
        function updateTransforms(obj)
            ax = gca;
            ax.XLim = [obj.RF_wheel(1,4)-3 obj.RF_wheel(1,4)+3];
            ax.YLim = [obj.RF_wheel(2,4)-3 obj.RF_wheel(2,4)+3];
            ax.ZLim = [obj.RF_wheel(3,4)-3 obj.RF_wheel(3,4)+3];
            % Updates the transform matrices.
            campos(obj.RF_cam(1:3,4));
            camtarget(obj.RF_wheel(1:3,4));
            obj.Rig_up(1).Matrix  = obj.RF_up_rig;
            obj.Rig_low(1).Matrix = obj.RF_low_rig;
            obj.Wheel(1).Matrix   = obj.RF_wheel;
            drawnow
        end
    end
end
