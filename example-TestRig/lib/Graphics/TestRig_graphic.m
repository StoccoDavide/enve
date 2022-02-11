%
% File: TestRig_graphic.m
%
classdef TestRig_graphic < handle
    % A class for implementing a MATLAB Graphics visualization of the Tire
    % Test Rig
    
    properties (SetAccess=private)
        transf;
        rig_up;
        rig_low;
        wheel;
        Rig_up              = gobjects(1,1);
        Rig_low             = gobjects(1,1);
        Wheel               = gobjects(1,1);
        Trace_wheel         = gobjects(1,1);
        Trace_cp            = gobjects(1,1);
        G_RF_wheel          = gobjects(1,1);
        G_RF_wheelHub       = gobjects(1,1);
        G_RF_cp             = gobjects(1,1);
        G_normal            = gobjects(1,1);
        G_forces            = gobjects(1,3);
        G_moments           = gobjects(1,3);
        en_trace_wheel      = 1;
        en_trace_cp         = 1;
        en_RF_wheel         = 1;
        en_RF_cp            = 1;
        en_RF_wheelHub      = 1;
        en_normal           = 1;
        en_forces           = 1;
        en_moments          = 1;
        en_realdim_scale    = 1;
        RF_up_rig           = eye(4);
        RF_low_rig          = eye(4);
        RF_wheel            = eye(4);
        RF_cam              = eye(4) +[zeros(4,3) [ones(3,1) ; 0]];
        RF_cp               = eye(4);
        RF_wheelHub         = eye(4);
    end
    
    %% Public methods
    methods
        function obj = TestRig_graphic(rig_up_stl,rig_up_stl_scale,rig_low_stl,rig_low_stl_scaale,wheel_stl,wheel_stl_scale, RF_up_rig, RF_low_rig, RF_wheel, RF_cam, RF_cp, RF_wheelHub, R_tire, B_tire, rho, STI_forces, STI_moments, en_realdim_scale, en_trace_wheel, en_trace_cp, en_RF_wheel, en_RF_cp, en_RF_wheelHub, en_normal, en_forces, en_moments)
            
            obj.en_realdim_scale    = en_realdim_scale;
            obj.en_trace_wheel      = en_trace_wheel;
            obj.en_trace_cp         = en_trace_cp;
            obj.en_RF_wheel         = en_RF_wheel;
            obj.en_RF_cp            = en_RF_cp;
            obj.en_RF_wheelHub      = en_RF_wheelHub;
            obj.en_normal           = en_normal;
            obj.en_forces           = en_forces;
            obj.en_moments          = en_moments;
            
            % setup graphics
            ax = gca;                               % get current graphic axis
            view(3);
            obj.transf = hgtransform('Parent', ax);     % create obj.transforms
            
            % Create Bodies objects
            obj.Rig_up(1)   = hgtransform('Parent', obj.transf);
            createObj(obj, rig_up_stl,obj.Rig_up(1),'red',0.8,rig_up_stl_scale);
            
            obj.Rig_low(1) = hgtransform('Parent', obj.transf);
            createObj(obj, rig_low_stl,obj.Rig_low(1),'yellow',0.8,rig_low_stl_scaale);
            
            obj.Wheel(1) = hgtransform('Parent', obj.transf);
            createWheel(obj, wheel_stl,1,obj.Wheel(1),'black',0.5,wheel_stl_scale,R_tire,B_tire,en_realdim_scale);
            
            if obj.en_RF_wheel
                obj.G_RF_wheel(1) = hgtransform('Parent', obj.transf);
                createRF(obj, obj.G_RF_wheel(1), 'yellow');
            end
            
            if obj.en_RF_wheelHub
                obj.G_RF_wheelHub(1) = hgtransform('Parent', obj.transf);
                createRF(obj, obj.G_RF_wheelHub(1), 'yellow');
            end
            
            if obj.en_RF_cp
                obj.G_RF_cp(1) = hgtransform('Parent', obj.transf);
                createRF(obj, obj.G_RF_cp(1), 'blue');
            end
            
%             if obj.en_normal
%                 obj.G_normal(1) = hgtransform('Parent', obj.transf);
%             end
%             
%             if obj.en_forces
%                 obj.G_forces(1) = hgtransform('Parent', obj.transf);
%             end
%             
%             if obj.en_moments
%                 obj.G_moments(1) = hgtransform('Parent', obj.transf);
%             end
            
            % Create the traces
            if obj.en_trace_wheel
                obj.Trace_wheel(1) = animatedline('Parent', ax, 'MaximumNumPoints', 1000, 'Color', [0 0.4470 0.7410], 'LineWidth',2);
            end
            
            if obj.en_trace_cp
                obj.Trace_cp(1) = animatedline('Parent', ax, 'MaximumNumPoints', 1000, 'Color', [0.9294 0.6941 0.1255], 'LineWidth',2);
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
            obj.RF_up_rig   = RF_up_rig;
            obj.RF_low_rig  = RF_low_rig;
            obj.RF_wheel    = RF_wheel;
            obj.RF_cam      = RF_cam;
            obj.RF_cp       = RF_cp;
            obj.RF_wheelHub = RF_wheelHub;
            
            % first graphic update
            obj.updateTransforms();
            
        end
        
        function step(obj, RF_up_rig, RF_low_rig, RF_wheel, RF_cam, RF_cp, RF_wheelHub, rho, STI_forces, STI_moments)
            % Update graphic objects.
            obj.RF_up_rig   = RF_up_rig;
            obj.RF_low_rig  = RF_low_rig;
            obj.RF_wheel    = RF_wheel;
            obj.RF_cam      = RF_cam;
            obj.RF_cp       = RF_cp;
            obj.RF_wheelHub = RF_wheelHub;
            
            % update traces
            if obj.en_trace_wheel
                if (RF_wheel(1,4) ~= 0 || RF_wheel(2,4) ~= 0 || RF_wheel(3,4) ~= 0) % !workaround for trace point to origin at first step
                    obj.Trace_wheel.addpoints(RF_wheel(1,4),RF_wheel(2,4),RF_wheel(3,4));
                end
            end
            
            if obj.en_trace_cp
                if (RF_cp(1,4) ~= 0 || RF_cp(2,4) ~= 0 || RF_cp(3,4) ~= 0) % !workaround for trace point to origin at first step
                    obj.Trace_cp.addpoints(RF_cp(1,4),RF_cp(2,4),RF_cp(3,4));
                end
            end
            
            % update normal
            if obj.en_normal
                delete(obj.G_normal(1));
                obj.G_normal(1) = hgtransform('Parent', obj.transf);
                createArrow(obj, RF_cp(1:3,4) , RF_cp(1:3,3) * rho * 100, obj.G_normal(1), [0.6350 0.0780 0.1840], 3);
            end
            
            % update forces
            if obj.en_forces
                delete(obj.G_forces(1));
                obj.G_forces(1) = hgtransform('Parent', obj.transf);
                createCone(obj, [1,0,0] * STI_forces(1)/1000, obj.G_forces(1), [0.3922 0.8314 0.0745], 0.05 * STI_forces(1)/1000, 0.3);
                obj.G_forces(1).Matrix = obj.RF_wheelHub;
                
                delete(obj.G_forces(2));
                obj.G_forces(2) = hgtransform('Parent', obj.transf);
                createCone(obj, [0,1,0] * STI_forces(2)/1000, obj.G_forces(2), [0.3922 0.8314 0.0745], 0.05 * STI_forces(2)/1000, 0.3);
                obj.G_forces(2).Matrix = obj.RF_wheelHub;
                
                delete(obj.G_forces(3));
                obj.G_forces(3) = hgtransform('Parent', obj.transf);
                createCone(obj, [0,0,1] * STI_forces(3)/1000, obj.G_forces(3), [0.3922 0.8314 0.0745], 0.05 * STI_forces(3)/1000, 0.3);
                obj.G_forces(3).Matrix = obj.RF_wheelHub;
            end
            
            % update moments
            if obj.en_moments
                delete(obj.G_moments(1));
                obj.G_moments(1) = hgtransform('Parent', obj.transf);
                createCone(obj, [1,0,0] * STI_moments(1)/1000, obj.G_moments(1), [0.7176 0.2745 1.0000], 0.2 * STI_moments(1)/1000, 0.3);
                obj.G_moments(1).Matrix = obj.RF_wheelHub;
                
                delete(obj.G_moments(2));
                obj.G_moments(2) = hgtransform('Parent', obj.transf);
                createCone(obj, [0,1,0] * STI_moments(2)/1000, obj.G_moments(2), [0.7176 0.2745 1.0000], 0.2 * STI_moments(2)/1000, 0.3);
                obj.G_moments(2).Matrix = obj.RF_wheelHub;
                
                delete(obj.G_moments(3));
                obj.G_moments(3) = hgtransform('Parent', obj.transf);
                createCone(obj, [0,0,1] * STI_moments(3)/1000, obj.G_moments(3), [0.7176 0.2745 1.0000], 0.2 * STI_moments(3)/1000, 0.3);
                obj.G_moments(3).Matrix = obj.RF_wheelHub;
            end
            
            
            % update objects positions
            obj.updateTransforms();
            
        end
        
        function clearTraces(obj)
            % Call this to clear the traces.
            obj.Trace_wheel.clearpoints();
            obj.Trace_cp.clearpoints();
        end
        
        function destroy(obj)
            % Call this to clear the figure 
            delete(obj.Rig_up(1));
            delete(obj.Rig_low(1));
            delete(obj.Wheel(1));
            delete(obj.Trace_wheel(1));
            delete(obj.Trace_cp(1));
            delete(obj.G_RF_wheel(1));
            delete(obj.G_RF_wheelHub(1));
            delete(obj.G_RF_cp(1));
            delete(obj.G_normal(1));
            delete(obj.G_forces(1));
            delete(obj.G_forces(2));
            delete(obj.G_forces(3));
            delete(obj.G_moments(1));
            delete(obj.G_moments(2));
            delete(obj.G_moments(3));
            drawnow
        end
        
        function r = isAlive(obj)
            % Call this to check whether the figure window is still alive.
            r = isvalid(obj)                    && ...
                isvalid(obj.Rig_up(1))          && ...
                isvalid(obj.Rig_low(1))         && ...
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
        
        function createWheel(~, stl_wheel,mir,parent,color,transparency,scale,R_tire,B_tire,en_realdim_scale)
            % Creates the geometry
            % Assign patches
            temp_wheel   = stlread(stl_wheel);
            
            if en_realdim_scale
                R = R_tire;
                B = B_tire;
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
        
        function createArrow(~, origin, components, parent, color, thickness)
            quiver3(origin(1),origin(2),origin(3),components(1),components(2),components(3), ...
                    'Color', color,                                                          ...
                    'Parent', parent,                                                        ...
                    'LineWidth',thickness                                                    ...
                    );
        end
        
        function createCylinder(obj, components, parent, color, radius, transparency)
            [x,y,z] = cylinder(radius,10);
            x_ang = atan2(-components(2),components(3));
            y_ang = atan2(components(1),components(3));
            length = sqrt(components(1)^2+components(2)^2+components(3)^2);
            
            z = z*length;
            
            [x,y,z] = Xrotate(obj,x,y,z,x_ang);
            [x,y,z] = Yrotate(obj,x,y,z,y_ang);
            
            surf(x,y,z,                                                 ...
                     'Parent' , parent,                                 ...
                     'FaceColor', color,                                ...
                     'FaceLighting', 'gouraud',                         ...
                     'FaceAlpha',     transparency,                     ...
                     'EdgeColor',    'none'                             ...
                     );
        end
        
        function createCone(obj, components, parent, color, radius, transparency)
            [x,y,z] = cylinder([0,radius],10);
            x_ang = atan2(-components(2),components(3));
            y_ang = atan2(components(1),components(3));
            length = sqrt(components(1)^2+components(2)^2+components(3)^2);
            
            z = z*length;
            
            [x,y,z] = Xrotate(obj,x,y,z,x_ang);
            [x,y,z] = Yrotate(obj,x,y,z,y_ang);
            
            surf(x,y,z,                                                 ...
                     'Parent' , parent,                                 ...
                     'FaceColor', color,                                ...
                     'FaceLighting', 'gouraud',                         ...
                     'FaceAlpha',     transparency,                     ...
                     'EdgeColor',    'none'                             ...
                     );
        end
        
        function createPoint(~, coords, parent, color, radius)
            [x,y,z] = sphere(10);
            surf(x*radius+coords(1),y*radius+coords(2),z*radius+coords(3),      ...
                     'Parent' , parent,                                         ...
                     'FaceColor', color,                                        ...
                     'EdgeColor',    'none'                                     ...
                     );
        end
        
        function createRF(obj, parent, color)
            createPoint(obj, [0,0,0], parent, color, 0.01);
            
            %createArrow(obj, [0,0,0], [1,0,0].*0.1, parent, 'red', 3);
            %createArrow(obj, [0,0,0], [0,1,0].*0.1, parent, 'green', 3);
            %createArrow(obj, [0,0,0], [0,0,1].*0.1, parent, 'blue', 3);
            
            createCylinder(obj, [1,0,0].*0.1, parent, 'red', 0.005, 1);
            createCylinder(obj, [0,1,0].*0.1, parent, 'green', 0.005, 1);
            createCylinder(obj, [0,0,1].*0.1, parent, 'blue', 0.005, 1);
        end
        
        function [X,Y,Z] = Xrotate(~,x,y,z,theta)
            X = x;
            Y = y*cos(theta) - z*sin(theta);
            Z = y*sin(theta) + z*cos(theta);
        end
        
        function [X,Y,Z] = Yrotate(~,x,y,z,theta)
            X = x*cos(theta) + z*sin(theta);
            Y = y;
            Z = z*cos(theta) - x*sin(theta);
        end
        
        function [X,Y,Z] = Zrotate(~,x,y,z,theta)
            X = x*cos(theta) - y*sin(theta);
            Y = x*sin(theta) + y*cos(theta);
            Z = z;
        end
        
        function updateTransforms(obj)
            ax = gca;
            ax.XLim = [obj.RF_wheel(1,4)-3 obj.RF_wheel(1,4)+3];
            ax.YLim = [obj.RF_wheel(2,4)-3 obj.RF_wheel(2,4)+3];
            ax.ZLim = [obj.RF_wheel(3,4)-3 obj.RF_wheel(3,4)+3];
            % Updates the obj.transform matrices.
            campos(obj.RF_cam(1:3,4));
            camtarget(obj.RF_wheel(1:3,4));
            obj.Rig_up(1).Matrix        = obj.RF_up_rig;
            obj.Rig_low(1).Matrix       = obj.RF_low_rig;
            obj.Wheel(1).Matrix         = obj.RF_wheel;
            if obj.en_RF_wheel
                obj.G_RF_wheel(1).Matrix    = obj.RF_wheel;
            end
            if obj.en_RF_wheelHub
                obj.G_RF_wheelHub(1).Matrix    = obj.RF_wheelHub;
            end
            if obj.en_RF_cp
                obj.G_RF_cp(1).Matrix    = obj.RF_cp;
            end
            drawnow
        end
    end
end
