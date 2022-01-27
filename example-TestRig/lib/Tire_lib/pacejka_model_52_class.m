classdef pacejka_model_52_class < handle
    % CLASS for pacejka model 5.2   %% Pacejka Model 1996
    %
    % Public Methods Descriptions:
    %   - pacejka_model_62_class(tire_data,USE_MODE) -> initialize class
    %   - compute_forces(F_z,kappa,alpha,phi_t,V_x,omega,gamma,p_i,tire_data [optional])
    %   - compute_slips(F_z, Vx, Vy, omega, psi_dot, p_i)
    %   - compute_corrected_slips(kappa, alpha, phi_t, V_x, V_sx, V_sy, F_z, p_i)
    %   - compute_relax(phi_t, F_z, p_i)
    %   - compute_slips_dot(kappa_first, alpha_first, kappa, alpha, sigma_k, sigma_a, gamma, phi_t, omega, V_x, F_z, p_i)
    %   - update_lambda(pacejkaParam)
    
    properties (Constant)
        % constant properties
        
        epsilon_x = 1e-4;
        epsilon_y = 1e-4;
        epsilon_K = 1e-4;
        epsilon_V = 1e-1;
        epsilon_r = 1e-2;
        
    end % constant properties
    
    properties (SetAccess = private)
        
        % Scaling Factors
        %----------------
        
        lambda_Fz0;                  % Scale factor of nominal (rated) load
        lambda_muV;                  % with slip speed Vs decaying friction
        lambda_mux;               	 % Scale factor of Fx peak friction coefficient
        lambda_xk;                   % Scale factor of brake slp stiffness
        lambda_Hx;               	 % Scale factor of Fx horizontal shift
        lambda_Cx;               	 % Scale factor of Fx shape factor
        lambda_Ex;               	 % Scale factor of Fx curvature factor
        lambda_Vx;               	 % Scale factor of Fx vertical shift
        
        lambda_muy;               	 % Scale factor of Fy peak friction coefficient
        lambda_Hy;              	 % Scale factor of Fy horizontal shift
        lambda_Cy;               	 % Scale factor of Fy shape factor
        lambda_Ey;               	 % Scale factor of Fy curvature factor
        lambda_Vy;              	 % Scale factor of Fy vertical shift
        lambda_Kya;              	 % Scale factor of kappa influence on Fy
        lambda_Kygamma;              % Scale factor of camber force stiffness
        
        lambda_t;               	 % Scale factor of peak of pneumatic trail
        lambda_Mr;               	 % Scale factor for offset of residual torque
        lambda_Kzgamma;              % Scale factor of camber torque stiffness
        
        lambda_yk;               	 % Scale factor of Fy cornering stiffness
        lambda_xa;               	 % Scale factor of alpha influence on Fx
        lambda_Vyk;               	 % Scale factor of kappa induced Fy
        lambda_VMx;               	 % Scale factor of Mx vertical shift
        lambda_Mx;               	 % Scale factor of overturning couple
        lambda_My;               	 % Scale factor of rolling resistance torque
        lambda_MP;               	 % Scale factor of Parking Moment
        
        lambda_S;               	 % Scale factor of moment arm of Fx
        
        
        % pacejka parameters
        % .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
        
                RBY1;
        RBY2;
        RBY3;
        RCY1;
        RHY1;
        RVY1;
        RVY2;
        RVY3;
        RVY4;
        RVY5;
        RVY6;
        RBX1;
        RBX2;
        RCX1;
        RHX1;
        PCY1;
        PDY1;
        PDY2;
        PDY3;
        PEY1;
        PEY2;
        PEY3;
        PEY4;
        PHY1;
        PHY2;
        PHY3;
        PKY1;
        PKY2;
        PKY3;
        PVY1;
        PVY2;
        PVY3;
        PVY4;
        QBZ1;
        QBZ2;
        QBZ3;
        QBZ4;
        QBZ5;
        QBZ9;
        QBZ10;
        QCZ1;
        QDZ1;
        QDZ2;
        QDZ3;
        QDZ4;
        QDZ6;
        QDZ7;
        QDZ8;
        QDZ9;
        QEZ1;
        QEZ2;
        QEZ3;
        QEZ4;
        QEZ5;
        QHZ1;
        QHZ2;
        QHZ3;
        QHZ4;
        PCX1;
        PDX1;
        PDX2;
        PDX3;
        PEX1;
        PEX2;
        PEX3;
        PEX4;
        PHX1;
        PHX2;
        PKX1;
        PKX2;
        PKX3;
        PVX1;
        PVX2;

        F_z0;
        R_0;
        p_i0;

        PKY4;
        PKY6;
        PKY7;

        PCFX1;
        PCFX2;
        
        PCFY1;
        PCFY2;

        BREFF;
        DREFF;
        FREFF;
        Q_RE0;
        Q_V1;
        Q_V2;
        Q_FZ2;
        Q_FCX;
        Q_FCY;
        Q_FCY2;
        Q_CAM1;
        Q_CAM2;
        Q_CAM3;
        Q_FYS1;
        Q_FYS2;
        Q_FYS3;

        Q_RA1;
        Q_RA2;
        
        long_stiff;
        lat_stiff;
        ver_stiff;
        ver_damping;
        rim_radius;
        bott_offst;
        bott_stiff;
        
        V_low;
        V_0;
        
        ASPECT_RATIO;
        WIDTH;
        
        g;
        
        A_mu;
        
        
        kVlow0_k;  % longitudinal slip damping coefficient for low speed
        kVlow0_a;  % side slip damping coefficient for low speed
        
        sigma_k_min;  % minimum value for longitudinal slip relaxation length
        sigma_a_min;  % minimum value for side slip relaxation length
        sigma_p_min;  % minimum value for turn slip relaxation length
        sigma_k_max;  % maximum value for longitudinal slip relaxation length
        sigma_a_max;  % maximum value for side slip relaxation length
        sigma_p_max;  % maximum value for turn slip relaxation length
        
        rho_dot_max;  % value for upper saturation of rho_dot
        rho_dot_min;  % value for lower saturation of rho_dot
        
        USE_MODE;
        USE_MODE_1;
        USE_MODE_2;
        USE_MODE_sgn;
        USE_MODE_FIT; % use mode for fitting
        
    end % private properties
    
    properties
        
        % computed properties
        F_x0;
        F_y0;
        M_z0;
        F_x;
        F_y;
        M_z;
        M_x;
        M_y;
        
        F_y0_gamma0_phit0;
        
    end
    
    %% Methods %%
    methods
        
        function obj = pacejka_model_52_class(pacejkaParam,USE_MODE)
            % constructor method
            % INPUTS :
            % - pacejkaParam -> pacejka parameters structure
            % - USE_MODE     -> specifies the type of calculation performed:
            %       0: Fz only, no Magic Formula evaluation
            %       1: Fx,My only
            %       2: Fy,Mx,Mz only
            %       3: Fx,Fy,Mx,My,Mz uncombined force./moment calculation
            %       4: Fx,Fy,Mx,My,Mz combined force./moment calculation
            %       5: Fx,Fy,Mx,My,Mz combined force./moment calculation +
            %       turn slip
            %     +10: transient
            %     .*-1: mirroring of tyre characteristics
            %
            %       9: special mode for fitting 
            %           -> +100 pure longitudinal
            %           -> +200 pure lateral
            %           -> +300 pure combined
            
            % Coefficients
            obj.RBY1 = obj.checkfield(pacejkaParam,'RBY1');
            obj.RBY2 = obj.checkfield(pacejkaParam,'RBY2');
            obj.RBY3 = obj.checkfield(pacejkaParam,'RBY3');
            obj.RCY1 = obj.checkfield(pacejkaParam,'RCY1');
            obj.RHY1 = obj.checkfield(pacejkaParam,'RHY1');
            obj.RVY1 = obj.checkfield(pacejkaParam,'RVY1');
            obj.RVY2 = obj.checkfield(pacejkaParam,'RVY2');
            obj.RVY3 = obj.checkfield(pacejkaParam,'RVY3');
            obj.RVY4 = obj.checkfield(pacejkaParam,'RVY4');
            obj.RVY5 = obj.checkfield(pacejkaParam,'RVY5');
            obj.RVY6 = obj.checkfield(pacejkaParam,'RVY6');
            obj.RBX1 = obj.checkfield(pacejkaParam,'RBX1');
            obj.RBX2 = obj.checkfield(pacejkaParam,'RBX2');
            obj.RCX1 = obj.checkfield(pacejkaParam,'RCX1');
            obj.RHX1 = obj.checkfield(pacejkaParam,'RHX1');
            obj.PCY1 = obj.checkfield(pacejkaParam,'PCY1');
            obj.PDY1 = obj.checkfield(pacejkaParam,'PDY1');
            obj.PDY2 = obj.checkfield(pacejkaParam,'PDY2');
            obj.PDY3 = obj.checkfield(pacejkaParam,'PDY3');
            obj.PEY1 = obj.checkfield(pacejkaParam,'PEY1');
            obj.PEY2 = obj.checkfield(pacejkaParam,'PEY2');
            obj.PEY3 = obj.checkfield(pacejkaParam,'PEY3');
            obj.PEY4 = obj.checkfield(pacejkaParam,'PEY4');
            obj.PHY1 = obj.checkfield(pacejkaParam,'PHY1');
            obj.PHY2 = obj.checkfield(pacejkaParam,'PHY2');
            obj.PHY3 = obj.checkfield(pacejkaParam,'PHY3');
            obj.PKY1 = obj.checkfield(pacejkaParam,'PKY1');
            obj.PKY2 = obj.checkfield(pacejkaParam,'PKY2');
            obj.PKY3 = obj.checkfield(pacejkaParam,'PKY3');
            obj.PVY1 = obj.checkfield(pacejkaParam,'PVY1');
            obj.PVY2 = obj.checkfield(pacejkaParam,'PVY2');
            obj.PVY3 = obj.checkfield(pacejkaParam,'PVY3');
            obj.PVY4 = obj.checkfield(pacejkaParam,'PVY4');
            obj.QBZ1 = obj.checkfield(pacejkaParam,'QBZ1');
            obj.QBZ2 = obj.checkfield(pacejkaParam,'QBZ2');
            obj.QBZ3 = obj.checkfield(pacejkaParam,'QBZ3');
            obj.QBZ4 = obj.checkfield(pacejkaParam,'QBZ4');
            obj.QBZ5 = obj.checkfield(pacejkaParam,'QBZ5');
            obj.QBZ9 = obj.checkfield(pacejkaParam,'QBZ9');
            obj.QBZ10 =obj.checkfield(pacejkaParam,'QBZ10');
            obj.QCZ1 = obj.checkfield(pacejkaParam,'QCZ1');
            obj.QDZ1 = obj.checkfield(pacejkaParam,'QDZ1');
            obj.QDZ2 = obj.checkfield(pacejkaParam,'QDZ2');
            obj.QDZ3 = obj.checkfield(pacejkaParam,'QDZ3');
            obj.QDZ4 = obj.checkfield(pacejkaParam,'QDZ4');
            obj.QDZ6 = obj.checkfield(pacejkaParam,'QDZ6');
            obj.QDZ7 = obj.checkfield(pacejkaParam,'QDZ7');
            obj.QDZ8 = obj.checkfield(pacejkaParam,'QDZ8');
            obj.QDZ9 = obj.checkfield(pacejkaParam,'QDZ9');
            obj.QEZ1 = obj.checkfield(pacejkaParam,'QEZ1');
            obj.QEZ2 = obj.checkfield(pacejkaParam,'QEZ2');
            obj.QEZ3 = obj.checkfield(pacejkaParam,'QEZ3');
            obj.QEZ4 = obj.checkfield(pacejkaParam,'QEZ4');
            obj.QEZ5 = obj.checkfield(pacejkaParam,'QEZ5');
            obj.QHZ1 = obj.checkfield(pacejkaParam,'QHZ1');
            obj.QHZ2 = obj.checkfield(pacejkaParam,'QHZ2');
            obj.QHZ3 = obj.checkfield(pacejkaParam,'QHZ3');
            obj.QHZ4 = obj.checkfield(pacejkaParam,'QHZ4');
            obj.PCX1 = obj.checkfield(pacejkaParam,'PCX1');
            obj.PDX1 = obj.checkfield(pacejkaParam,'PDX1');
            obj.PDX2 = obj.checkfield(pacejkaParam,'PDX2');
            obj.PDX3 = obj.checkfield(pacejkaParam,'PDX3');
            obj.PEX1 = obj.checkfield(pacejkaParam,'PEX1');
            obj.PEX2 = obj.checkfield(pacejkaParam,'PEX2');
            obj.PEX3 = obj.checkfield(pacejkaParam,'PEX3');
            obj.PEX4 = obj.checkfield(pacejkaParam,'PEX4');
            obj.PHX1 = obj.checkfield(pacejkaParam,'PHX1');
            obj.PHX2 = obj.checkfield(pacejkaParam,'PHX2');
            obj.PKX1 = obj.checkfield(pacejkaParam,'PKX1');
            obj.PKX2 = obj.checkfield(pacejkaParam,'PKX2');
            obj.PKX3 = obj.checkfield(pacejkaParam,'PKX3');
            obj.PVX1 = obj.checkfield(pacejkaParam,'PVX1');
            obj.PVX2 = obj.checkfield(pacejkaParam,'PVX2');
            
            obj.F_z0  = obj.checkfield(pacejkaParam,'FNOMIN');
            obj.R_0   = obj.checkfield(pacejkaParam,'UNLOADED_RADIUS');
            obj.p_i0  = 0;                 % nominal tire inflation pressure (not used in MF 5.2)
                   
            obj.PKY4 = obj.checkfield(pacejkaParam,'PKY4');
            obj.PKY6 = obj.checkfield(pacejkaParam,'PKY6');
            obj.PKY7 = obj.checkfield(pacejkaParam,'PKY7');
           
            obj.PCFX1  = obj.checkfield(pacejkaParam,'PCFX1');
            obj.PCFX2  = obj.checkfield(pacejkaParam,'PCFX2');
            
            obj.PCFY1  = obj.checkfield(pacejkaParam,'PCFY1');
            obj.PCFY2  = obj.checkfield(pacejkaParam,'PCFY2');
            
            obj.BREFF  = obj.checkfield(pacejkaParam,'BREFF');
            obj.DREFF  = obj.checkfield(pacejkaParam,'DREFF');
            obj.FREFF  = obj.checkfield(pacejkaParam,'FREFF');
            obj.Q_RE0  =obj.checkfield(pacejkaParam,'Q_RE0');
            obj.Q_V1   =obj.checkfield(pacejkaParam,'Q_V1');
            obj.Q_V2   =obj.checkfield(pacejkaParam,'Q_V2');
            obj.Q_FZ2  =obj.checkfield(pacejkaParam,'Q_FZ2');
            obj.Q_FCX  =obj.checkfield(pacejkaParam,'Q_FCX');
            obj.Q_FCY  =obj.checkfield(pacejkaParam,'Q_FCY');
            obj.Q_FCY2  =obj.checkfield(pacejkaParam,'Q_FCY2');
            obj.Q_CAM1 =obj.checkfield(pacejkaParam,'Q_CAM1');
            obj.Q_CAM2 =obj.checkfield(pacejkaParam,'Q_CAM2');
            obj.Q_CAM3 =obj.checkfield(pacejkaParam,'Q_CAM3');
            obj.Q_FYS1 =obj.checkfield(pacejkaParam,'Q_FYS1');
            obj.Q_FYS2 =obj.checkfield(pacejkaParam,'Q_FYS2');
            obj.Q_FYS3 =obj.checkfield(pacejkaParam,'Q_FYS3');
           
            obj.Q_RA1   =obj.checkfield(pacejkaParam,'Q_RA1');
            obj.Q_RA2   =obj.checkfield(pacejkaParam,'Q_RA2');
            
            obj.long_stiff = obj.checkfield(pacejkaParam,'LONGITUDINAL_STIFFNESS');
            obj.lat_stiff  = obj.checkfield(pacejkaParam,'LATERAL_STIFFNESS');
            obj.ver_stiff  = obj.checkfield(pacejkaParam,'VERTICAL_STIFFNESS');
            obj.ver_damping=obj.checkfield(pacejkaParam,'VERTICAL_DAMPING');
            obj.rim_radius =obj.checkfield(pacejkaParam,'RIM_RADIUS');
            obj.bott_offst  =obj.checkfield(pacejkaParam,'BOTTOM_OFFST');
            obj.bott_stiff  =obj.checkfield(pacejkaParam,'BOTTOM_STIFF');
            
            obj.V_low  = obj.checkfield(pacejkaParam,'VXLOW');
            
            obj.ASPECT_RATIO = obj.checkfield(pacejkaParam,'ASPECT_RATIO');
            obj.WIDTH        = obj.checkfield(pacejkaParam,'WIDTH');
            
            obj.kVlow0_k = 770*4;   % 770 value suggested in table 8.4 Book
            obj.kVlow0_a = 770*2;   % 770 value suggested in table 8.4 Book
            
            obj.sigma_k_min  = 0.05;  % 0.2 -> value suggested in table 8.4 Book
            obj.sigma_a_min  = 0.05;  % 0.2 -> value suggested in table 8.4 Book
            obj.sigma_p_min  = 0.05;  % (0.5 is a relatively high value, but it prevents numerical instabilities)
            obj.sigma_k_max  = 0.4;   %
            obj.sigma_a_max  = 0.5;   %
            obj.sigma_p_max  = 0.2;   %
            
            obj.rho_dot_max  =  1;    %
            obj.rho_dot_min  = -1;    %
            
            obj.g = obj.checkfield(pacejkaParam,'GRAVITY');            % acceleration due to gravity
            
            if isfield(pacejkaParam,'LONGVL')    % check existance of LONGVL field
                obj.V_0 = pacejkaParam.LONGVL;       % reference velocity = specified value
            else
                obj.V_0 = sqrt(obj.g.*pacejkaParam.R_0);               % reference velocity = sqrt(gRo)
            end
            
            % Additional Parameters
            obj.A_mu = 10;           % suggestion A_mu =10
            
            % Scaling Factors
            obj.update_lambda(pacejkaParam);
            
            % USE MODE
            obj.USE_MODE = USE_MODE;
            if abs(obj.USE_MODE) < 100
                parsed_um = dec2base(abs(USE_MODE),10) - '0';
                parsed_um = [zeros(1,2-length(parsed_um)),parsed_um];
                obj.USE_MODE_1    = parsed_um(2);          % type of calculation
                obj.USE_MODE_2    = parsed_um(1);          % transient
                obj.USE_MODE_sgn  = obj.mysign(USE_MODE);  % flip tire
                obj.USE_MODE_FIT  = 0;                     % fitting step 
            else
                parsed_um = dec2base(abs(USE_MODE),10) - '0';
                parsed_um = [zeros(1,3-length(parsed_um)),parsed_um];
                obj.USE_MODE_1    = parsed_um(3);          % type of calculation
                obj.USE_MODE_2    = parsed_um(2);          % transient
                obj.USE_MODE_FIT  = parsed_um(1);          % fitting step 
                obj.USE_MODE_sgn  = obj.mysign(USE_MODE);  % flip tire
            end
            
        end % constructor method
        
        
        function val = checkfield(~,S,field) 
           % check field existance
           if isfield(S,field)
               val = S.(field);
           else
               val = NaN;
           end
        end % ceckfield
        
        
        function [F_x,F_y,M_x,M_y,M_z] = compute_forces(obj,F_z,kappa,alpha,phi_t,V_x,omega,gamma,~,varargin)
            % Computation of the total forces Fx, Fy and moment Mz
            
            % Required Inputs (Units and Sign Convention)
            % Fz: normal force (N)
            % kappa: slip ratio (%, i.e. 0.10 = 10%) where a + slip ratio generates a + driving force
            % alpha: slip angle (rad) where a + slip angle generates a
            % NEGATIVE lateral force (ISO convention)
            % phi_t: turn slip
            % omega: wheel angular velocity about rotation axis
            % V_x: longitudinal velocity of contact point
            % gamma: camber angle (rad) where a + camber angle indicates the top of the tire tipped right (same sign convention for left and right tires)
            % p_i: tire internal pressure.
            % tire_data [OPTIONAL]: tire data structure, if given the
            % lambda coefficient are updated with the value of the data
            % structure
            %
            % Resulting Outputs (Units and Sign Convention)
            % Fy : Lateral Force (N)
            % Fx : Longitudinal Force (N)
            % Mx : Overturning Couple (Nm)
            % My : Rolling Resistance Moment (Nm)
            % Mz : Aligning Torque (Nm)
            
            % Preprocessing
            % -------------
            
            if F_z>0  % check for positive wheel load
                
                
                % compute common variables
                [V_var,d_var,first_var] = obj.common(kappa,alpha,V_x,F_z,obj.p_i0);
                
                % compute Zitas
                Zita = obj.zita(F_z, kappa, alpha, gamma, phi_t, omega, V_var,d_var, first_var);
                
                alpha = alpha .* obj.USE_MODE_sgn;
                gamma = gamma .* obj.USE_MODE_sgn;
                phi_t = phi_t .* obj.USE_MODE_sgn;
                
                % update scaling factors if pacejka parameters are provided
                if nargin > 9
                    pacejkaParam = varargin{1};
                    obj.update_lambda(pacejkaParam);
                end
                
                
                if obj.USE_MODE_1 == 0
                    
                    % no MF computation recipe
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    F_x = 0;
                    F_y = 0;
                    M_x = 0;
                    M_y = 0;
                    M_z = 0;
                    
                elseif obj.USE_MODE_1 == 1
                    
                    % Fx,My force./moment recipe
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    obj.F_x0                  = obj.compute_F_x0(F_z,kappa,gamma,V_var,d_var,Zita);
                    obj.F_x = obj.F_x0;
                    
                    obj.M_y                   = 0;
                    
                    F_x =  obj.F_x;
                    F_y =  0;
                    M_x =  0;
                    M_y = obj.M_y;                        % - sign for ISO convention
                    M_z =  0;
                    
                    
                elseif obj.USE_MODE_1 == 2
                    
                    % Fy,Mx,Mz force./moment recipe
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    obj.F_y = obj.F_y0;
                    
                    obj.M_x                   = 0;
                    
                    obj.F_y0_gamma0_phit0     = obj.compute_F_y0(F_z,alpha,0,V_var,d_var,first_var,Zita);
                    
                    obj.M_z                   = obj.compute_M_z0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    
                    F_x =  0;
                    F_y = obj.F_y   .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    M_x =  obj.M_x   .* obj.USE_MODE_sgn;
                    M_y =  0;
                    M_z = obj.M_z  .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    
                    
                elseif obj.USE_MODE_1 == 3
                    
                    % Fx,Fy,Mx,My,Mz uncombined force./moment recipe
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    obj.F_x0                  = obj.compute_F_x0(F_z,kappa,gamma,V_var,d_var,Zita);
                    obj.F_x = obj.F_x0;
                    
                    obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    obj.F_y = obj.F_y0;
                    
                    obj.M_x                   = 0;
                    
                    obj.M_y                   = 0;
                    
                    obj.F_y0_gamma0_phit0     = obj.compute_F_y0(F_z,alpha,0,V_var,d_var,first_var,Zita);
                    
                    obj.M_z                   = obj.compute_M_z0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    
                    F_x =  obj.F_x;
                    F_y = obj.F_y  .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    M_x =  obj.M_x  .* obj.USE_MODE_sgn;
                    M_y = obj.M_y;                        % - sign for ISO convention
                    M_z = obj.M_z  .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    
                elseif obj.USE_MODE_1 == 4 || obj.USE_MODE_1 == 5
                    
                    % Fx,Fy,Mx,My,Mz combined force./moment recipe
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    obj.F_x0                  = obj.compute_F_x0(F_z,kappa,gamma,V_var,d_var,Zita);
                    obj.F_x                   = obj.compute_F_x_comb(kappa,alpha,gamma,d_var);
                    
                    obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    obj.F_y                   = obj.compute_F_y_comb(F_z,kappa,alpha,gamma,V_var,d_var,Zita);
                    
                    obj.M_x                   = 0;
                    
                    obj.M_y                   = 0;
                    
                    obj.F_y0_gamma0_phit0     = obj.compute_F_y0(F_z,alpha,0,V_var,d_var,first_var,Zita);
                    
                    obj.M_z0                  = obj.compute_M_z0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                    obj.M_z                   = obj.compute_M_z(F_z,kappa,alpha,gamma,V_var,d_var,first_var,Zita);
                    
                    F_x =  obj.F_x;
                    F_y = obj.F_y  .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    M_x =  obj.M_x  .* obj.USE_MODE_sgn;
                    M_y = obj.M_y;                        % - sign for ISO convention
                    M_z = obj.M_z  .* obj.USE_MODE_sgn;   % - sign for ISO convention
                    
                    
                elseif obj.USE_MODE_1 == 9
                    
                    % FITTING mode
                    %.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
                    
                    if obj.USE_MODE_FIT == 1
                        % pure long
                        
                        obj.F_x0                  = obj.compute_F_x0(F_z,kappa,gamma,V_var,d_var,Zita);
                        obj.F_x = obj.F_x0;
                        
                        
                        F_x =  obj.F_x;
                        F_y = 0;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = 0;   % - sign for ISO convention
                        
                    elseif obj.USE_MODE_FIT == 2
                        % pure lat
                        
                        obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                        obj.F_y = obj.F_y0;
                        
                        F_x = 0;
                        F_y = obj.F_y;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = 0;   % - sign for ISO convention
                        
                    elseif obj.USE_MODE_FIT == 3
                        % pure lat MZ
                        
                        obj.F_y0_gamma0_phit0     = obj.compute_F_y0(F_z,alpha,0,V_var,d_var,first_var,Zita);
                        obj.M_z                   = obj.compute_M_z0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                        
                        F_x = 0;
                        F_y = 0;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = obj.M_z;   % - sign for ISO convention
                        
                    elseif obj.USE_MODE_FIT == 4
                        % pure long
                        
                        obj.F_x0                  = obj.compute_F_x0(F_z,kappa,gamma,V_var,d_var,Zita);
                        obj.F_x                   = obj.compute_F_x_comb(kappa,alpha,gamma,d_var);
                        
                        
                        F_x =  obj.F_x;
                        F_y = 0;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = 0;   % - sign for ISO convention
                        
                    elseif obj.USE_MODE_FIT == 5
                        % pure lat FY
                        
                        obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                        obj.F_y                   = obj.compute_F_y_comb(F_z,kappa,alpha,gamma,V_var,d_var,Zita);
                        
                        F_x = 0;
                        F_y = obj.F_y;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = 0;   % - sign for ISO convention
                        
                    elseif obj.USE_MODE_FIT == 6
                        % pure lat MZ
                        
                        obj.F_y0                  = obj.compute_F_y0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                        obj.F_y                   = obj.compute_F_y_comb(F_z,kappa,alpha,gamma,V_var,d_var,Zita);
                        
                        obj.F_y0_gamma0_phit0     = obj.compute_F_y0(F_z,alpha,0,V_var,d_var,first_var,obj.zita(F_z, kappa, alpha, 0, 0, omega, V_var,d_var, first_var));
                        obj.M_z0                  = obj.compute_M_z0(F_z,alpha,gamma,V_var,d_var,first_var,Zita);
                        obj.M_z                   = obj.compute_M_z(F_z,kappa,alpha,gamma,V_var,d_var,first_var,Zita);
                        
                        F_x = 0;
                        F_y = 0;   % - sign for ISO convention
                        M_x = 0;
                        M_y = 0;   % - sign for ISO convention
                        M_z = obj.M_z;   % - sign for ISO convention
                        
                        else
                        
                        F_x = 0;
                        F_y = 0;
                        M_x = 0;
                        M_y = 0;
                        M_z = 0;
                        
                    end
                    
                else
                    
                    % warning('Invalid USE_mode');
                    
                    F_x = 0;
                    F_y = 0;
                    M_x = 0;
                    M_y = 0;
                    M_z = 0;
                    
                end % if USE_MODE
                
            else
                
                F_x = 0;
                F_y = 0;
                M_x = 0;
                M_y = 0;
                M_z = 0;
                
            end
            
            % additional check
            
            F_x(isnan(F_x)) = 0;
            
            F_y(isnan(F_y)) = 0;
            
            M_x(isnan(M_x)) = 0;
            
            M_y(isnan(M_y)) = 0;
            
            M_z(isnan(M_z)) = 0;
            
        end % compute_forces
        
        
        function [kappa,alpha,phi_t,Vsx,Vsy,R_e] = compute_slips(obj, Vcx, Vcy, omega, psi_dot, R_e)
            % Computation of the wheel slips kappa, alpha and phi_t
            
            % Required Inputs (Units and Sign Convention)
            % Fz: wheel normal force
            % Vx: contact point velocity in x direction (ISO)
            % Vy: contact point velocity in y direction (ISO)
            % omega: wheel angular velocity about rotation axis
            % psi_dot: tire angular velocity around z axis (ISO).
            % p_i: tire internal pressure.
            %
            %
            % Resulting Outputs (Units and Sign Convention)
            % kappa: longitudinal slip
            % alpha: slip angle (rad)
            % phi_t: turn slip
            
            % Longitudinal slip velocity
            Vsx = Vcx - R_e * omega;       % [Eqn (2.3) Page 64 - Book]
            
            % Lateral slip velocity
            Vsy = Vcy;
            
            % Check if is low speed
            isLowSpeed_x = max(abs(Vcx),abs(omega*R_e)) < obj.V_low ;
            
            % Longitudinal Slip
            if isLowSpeed_x
                % Low speed Slip Ratio Calculation
                kappa = -(2*Vsx/(obj.V_low  + (max([abs(Vcx),abs(omega*R_e),abs(Vsx)])^2)/obj.V_low) ); % correction for low speed (added Vsx in max for case of discordant speeds)
            else
                % Slip Ratio Calculation
                kappa = -(Vsx/max([abs(Vcx),abs(omega*R_e),abs(Vsx)])); % [Eqn (2.4) Page 64 - Book] (saturated at +-1)
            end
            
            
            % Check if is low speed
            isLowSpeed_y = abs(Vcx) < obj.V_low ;
            
            % Side Slip Angle
            if isLowSpeed_y
                % Low speed Side Slip Angle Calculation
                alpha = atan(2*Vsy/(obj.V_low  + (Vcx^2)/obj.V_low) );% correction for low speed  (without - sign for ISO convention)
            else
                % Side Slip Angle Calculation
                alpha = atan(Vsy/abs(Vcx)); % [Eqn (2.9) Page 67 - Book] (without - sign for ISO convention)
            end
            
            
            if obj.USE_MODE_1 == 5
                % Turn slip
                
                % contact point velocity magnitude
                Vc = sqrt(Vcx^2+Vcy^2);
                
                % avoid zero division
                Vc_first = Vc + obj.epsilon_V;
                
                % Calculate phit
                phi_t = psi_dot/Vc_first; % [Eqn (4.75) Page 183 - Book] (without - sign for ISO convention)
                
            else
                phi_t = 0;
            end
            
            
            kappa(isnan(kappa)) = 0;
            
            alpha(isnan(alpha)) = 0;
            
            phi_t(isnan(phi_t)) = 0;
            
            
        end % compute_slips
        
        
        
        function [kappa_corr,alpha_corr,phi_t_corr] = compute_corrected_slips(obj, kappa, alpha, phi_t, V_x, V_sx, V_sy, F_z, ~)
            % Computation of the corrected wheel slips kappa and alpha for
            % low speed
            
            % Required Inputs (Units and Sign Convention)
            % kappa: slip ratio (%, i.e. 0.10 = 10%) where a + slip ratio generates a + driving force
            % alpha: slip angle (rad) (ISO convention)
            % phi_t: turn slip
            % V_x: longitudinal velocity of contact point
            % V_sx: longitudinal component of slip velocity
            % V_sy: lateral component of slip velocity
            % F_z: normal force (N)
            % p_i: tire internal pressure.
            %
            %
            % Resulting Outputs (Units and Sign Convention)
            % kappa_corr: corrected longitudinal slip
            % alpha_corr: corrected side slip
            
            
            if F_z > 0
                
                % compute common variables
                [~,d_var,first_var] = obj.common(kappa, alpha, V_x, F_z, obj.p_i0);
                
                % Longitudinal slip correction
                %-----------------------------
                
                K_xk = F_z * (obj.PKX1 + obj.PKX2*d_var.df_z) * exp(obj.PKX3*d_var.df_z) * obj.lambda_xk;
                % longitudinal slip stiffness with lower treshold (obj.PKX1/5) which prevent an unfisable kappa_corr computation
                C_Fk = obj.PKX1 / 5 + K_xk^2/(obj.PKX1 / 5 + K_xk); 
                
                if abs(V_x) <= obj.V_low
                    kVlow_k = 1/2* obj.kVlow0_k*(1+cos(pi*abs(V_x)/obj.V_low));
                else
                    kVlow_k = 0;
                end
                
                kappa_corr = kappa - kVlow_k*(V_sx)/C_Fk;
                
                
                % Side slip correction
                %---------------------
                
                K_ya0 = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2)));
                % lateral slip stiffness with lower treshold (obj.PKY1/5) which prevent an unfisable alpha_corr computation
                C_Fa = -(obj.PKY1 / 5 + K_ya0^2/(obj.PKY1 / 5 + K_ya0)); % - for ISO convention (the cornering stiffness is negative)
                
                if abs(V_x) <= obj.V_low
                    kVlow_a = 1/2* obj.kVlow0_a*(1+cos(pi*abs(V_x)/obj.V_low));
                else
                    kVlow_a = 0;
                end
                
                alpha_corr = alpha - kVlow_a* (-V_sy)/C_Fa;
                
                % Turn slip correction
                %---------------------
                
                phi_t_corr = phi_t;
                
            else
                
                kappa_corr = 0;
                alpha_corr = 0;
                phi_t_corr = 0;
                
            end % if F_z
            
            kappa_corr(isnan(kappa_corr)) = 0;
            
            alpha_corr(isnan(alpha_corr)) = 0;
            
            phi_t_corr(isnan(phi_t_corr)) = 0;
            
        end % compute_corrected_slips
        
        
        
        function [sigma_k,sigma_a,sigma_p] = compute_relax(obj, phi_t, F_z, ~)
            % Computation of the relaxation lengths (LINEAR MODEL)
            
            % Required Inputs (Units and Sign Convention)
            % phi_t: turn slip
            % F_z: normal force (N)
            % p_i: tire internal pressure.
            %
            %
            % Resulting Outputs (Units and Sign Convention)
            % sigma_k: relaxaion length for longitudinal slip
            % sigma_a: relaxaion length for side slip
            % sigma_p: relaxaion length for turn slip
            
            
            if F_z > 0
            
                % Preprocessing
                % -------------

                % compute common variables
                [~,d_var,first_var] = obj.common(0, 0, 0, F_z, obj.p_i0); % no slips or velocity dependency in this function

                % Longitudinal slip relax
                %-----------------------------

                % Overall longitudinal tire stiffness at road level
                C_x0 = obj.long_stiff; %Tyre overall longitudinal stiffness
                C_x = C_x0*(1 + obj.PCFX1*d_var.df_z + obj.PCFX2*d_var.df_z^2); % (Eqn 17 - Paper )

                % Longitudinal slip stiffness
                K_xk = F_z * (obj.PKX1 + obj.PKX2*d_var.df_z) * exp(obj.PKX3*d_var.df_z) * obj.lambda_xk;
                C_Fk = K_xk;

                % Relaxation lengths for longitudinal and side-slip are:
                sigma_k = min(obj.sigma_k_max,max(C_Fk/C_x, obj.sigma_k_min)); % (Eqn 7.8 - Book)


                % Side slip relax
                %---------------------

                % Overall lateral tire stiffness at road level
                C_y0 = obj.lat_stiff; %Tyre overall lateral stiffness
                C_y = C_y0*(1 + obj.PCFY1*d_var.df_z + obj.PCFY2*d_var.df_z^2); % (Eqn 18 - Paper)

                % Lateral slip stiffness
                K_ya0 = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2)));
                C_Fa = - K_ya0; % - for ISO convention (the cornering stiffness is negative)

                % relaxation length for side slip
                sigma_a = min(obj.sigma_a_max,max(C_Fa/C_y, obj.sigma_a_min)); % (Eqn 7.6 - Book)


                % Turn slip relax
                %---------------------

                if obj.USE_MODE_1 == 5

                    % contact length a
                    a = obj.R_0 *(obj.Q_RA2 * F_z/(obj.ver_stiff * obj.R_0) + obj.Q_RA1 * sqrt(F_z/(obj.ver_stiff * obj.R_0)));

                    % simplified relaxation length for side slip
                    sigma_p = min(obj.sigma_p_max,max(a/2,obj.sigma_p_min));

                else
                    % relaxation length for side slip
                    sigma_p = 0;
                end
            else
                sigma_k = obj.sigma_p_min;
                sigma_a = obj.sigma_p_min;
                sigma_p = obj.sigma_p_min;
            end % if F_z
            
            sigma_k(isnan(sigma_k)) = obj.sigma_p_min;
            
            sigma_a(isnan(sigma_a)) = obj.sigma_p_min;
            
            sigma_p(isnan(sigma_p)) = obj.sigma_p_min;
            
            
        end % compute_relax
        
        
        
        function [kappa_first_dot,alpha_first_dot,phi_t_first_dot] = compute_slips_dot(obj, kappa_first, alpha_first, phi_t_first, kappa, alpha, phi_t, sigma_k, sigma_a, sigma_p, gamma, omega, V_x, F_z, ~)
            % Computation of the slips dynamics (LINEAR MODEL)
            
            % Required Inputs (Units and Sign Convention)
            % kappa_first: actual contact point slip ratio
            % alpha_first: actual contact point slip angle (ISO convention)
            % kappa: steady state value of slip ratio
            % alpha: steady state value of slip angle (ISO convention)
            % sigma_k: corrected longitudinal slip
            % sigma_a: corrected side slip
            % gamma: camber angle (rad)
            % phi_t: turn slip
            % omega: angular velocity about spin axis
            % V_x: longitudinal velocity of contact point
            % F_z: normal force (N)
            % p_i: tire internal pressure.
            %
            %
            % Resulting Outputs (Units and Sign Convention)
            % kappa_dot: time derivative value of longitudinal slip
            % alpha_dot: time derivative value of side slip
            
            
            % low speed limitation flags    [Eqn 7.25 Book] (SEE 7.2.2 BOOK)
            if abs(V_x) < obj.V_low
                
                % compute common variables
                [V_var,d_var,first_var] = obj.common(kappa, alpha, V_x, F_z, obj.p_i0); % no phi_t dependency in this function
                
                gammaStar = sin(gamma);
                lambdaStar_muy = obj.lambda_muy / (1+ obj.lambda_muV * V_var.V_s/obj.V_0);
                lambdaFirst_muy = obj.A_mu * lambdaStar_muy / (1 + (obj.A_mu - 1) * lambdaStar_muy);
                K_ya = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2))) .* (1 - obj.PKY3 .* abs(gammaStar));
                KFirst_ya = K_ya + obj.epsilon_K;
                K_y_gamma0 = F_z * (obj.PKY6 + obj.PKY7*d_var.df_z) * obj.lambda_Kygamma;
                S_Vygamma = F_z * (obj.PVY3 + obj.PVY4*d_var.df_z) * gammaStar * obj.lambda_Kygamma * lambdaFirst_muy;
                S_Hy = (obj.PHY1 + obj.PHY2*d_var.df_z) * obj.lambda_Hy + (K_y_gamma0 * gammaStar - S_Vygamma)/(K_ya + obj.epsilon_K);
                S_Vy = F_z * (obj.PVY1 + obj.PVY2*d_var.df_z) * obj.lambda_Vy * lambdaFirst_muy + S_Vygamma;
                S_Hf = S_Hy + S_Vy/KFirst_ya;
                alpha_r = tan(alpha_first) + S_Hf;
                K_xk = F_z * (obj.PKX1 + obj.PKX2*d_var.df_z) * exp(obj.PKX3*d_var.df_z) * obj.lambda_xk;
                alpha_req_first = sqrt(alpha_r^2 +  (K_xk/KFirst_ya)^2 * kappa_first^2) * obj.mysign(alpha_r);
                
                lambdaStar_muy = obj.lambda_muy / (1+ obj.lambda_muV * V_var.V_s/obj.V_0);
                mu_y = (obj.PDY1 + obj.PDY2*d_var.df_z) * (1-obj.PDY3*gammaStar^2) * lambdaStar_muy;
                D_y = mu_y * F_z;
                K_ya0 = obj.PKY1 * first_var.FFirst_z0 * sin(obj.PKY4*atan((F_z/first_var.FFirst_z0)/((obj.PKY2)))) * obj.lambda_Kya;
                C_Fa = - K_ya0; % - for ISO convention (the cornering stiffness is negative)
                alpha_sl = 3 * D_y/C_Fa;
                
                if abs(alpha_req_first) > alpha_sl
                    
                    if ((V_var.V_sx + abs(V_x) * kappa_first)* kappa_first * sigma_k) < 0
                        tk=0;
                    else
                        tk=1;
                    end
                    
                    if ((V_var.V_sy + abs(V_x) * alpha_first)* alpha_first * sigma_a) < 0
                        ta=0;
                    else
                        ta=1;
                    end
                    
                else
                    tk=1;
                    ta=1;
                end
                
            else
                tk=1;
                ta=1;
                
            end % if
            
            % transient longitudinal slip
            if tk
                % max(obj.V_low,abs(V_x)) prevent slips to stack when low
                % speed
                kappa_first_dot = 1/sigma_k * max(obj.V_low,abs(V_x)) * (kappa - kappa_first); % [chapter 7 book ]
            else
                kappa_first_dot = 0;
            end
            
            % transient lateral slip
            if ta
                % max(obj.V_low,abs(V_x)) prevent slips to stack when low
                % speed
                alpha_first_dot = 1/sigma_a * max(obj.V_low,abs(V_x)) * (alpha - alpha_first); % [chapter 7 book eq 7.18  pag 333]
            else
                alpha_first_dot = 0;
            end
            
            % transient turn slip
            if obj.USE_MODE_1 == 5
                % max(obj.V_low,abs(V_x)) prevent slips to stack when low
                % speed
                phi_t_first_dot = 1/sigma_p * max(obj.V_low,abs(V_x)) * (phi_t - phi_t_first);
            else
                phi_t_first_dot = 0;
            end
            
            kappa_first_dot(isnan(kappa_first_dot)) = 0;
            
            alpha_first_dot(isnan(alpha_first_dot)) = 0;
            
            phi_t_first_dot(isnan(phi_t_first_dot)) = 0;
            
        end % compute_slips_dot
        
        
        
        function obj = update_lambda(obj,pacejkaParam)
            % Scaling Factors
            obj.lambda_Fz0      = pacejkaParam.LFZO ;               % nominal (rated) load
            if isfield(pacejkaParam,'LMUV')                         % check existance of LMUV field
                obj.lambda_muV = pacejkaParam.LMUV;
            else
                obj.lambda_muV = 0;                                 % 0 if not used
            end
            obj.lambda_mux      = pacejkaParam.LMUX ;
            obj.lambda_xk       = pacejkaParam.LKX ;
            obj.lambda_Hx       = pacejkaParam.LHX ;
            obj.lambda_Cx       = pacejkaParam.LCX ;
            obj.lambda_Ex       = pacejkaParam.LEX ;
            obj.lambda_Vx       = pacejkaParam.LVX ;
            
            obj.lambda_muy      = pacejkaParam.LMUY ;
            obj.lambda_Hy       = pacejkaParam.LHY ;
            obj.lambda_Cy       = pacejkaParam.LCY ;
            obj.lambda_Ey       = pacejkaParam.LEY ;
            obj.lambda_Vy       = pacejkaParam.LVY ;
            obj.lambda_Kya      = pacejkaParam.LYKA ;
            obj.lambda_Kygamma  = pacejkaParam.LKYC ;
            
            obj.lambda_t        = pacejkaParam.LTR ;
            obj.lambda_Mr       = pacejkaParam.LRES ;
            obj.lambda_Kzgamma  = pacejkaParam.LKZC ;
            
            obj.lambda_yk       = pacejkaParam.LKY ;
            obj.lambda_xa       = pacejkaParam.LXAL ;
            obj.lambda_Vyk      = pacejkaParam.LVYKA ;
            obj.lambda_VMx      = pacejkaParam.LVMX ;
            obj.lambda_Mx       = pacejkaParam.LMX ;
            obj.lambda_My       = pacejkaParam.LMY ;
            obj.lambda_MP       = pacejkaParam.LMP ;
            
            obj.lambda_S        = pacejkaParam.LS ;                 % M_z moment arm of F_x
            
        end % update_lambda
        
        
        function F_z = compute_F_z(obj,rho, rho_dot,omega,gamma,~,F_x,F_y) % (See MFeval library)
            % Compute F_z force
            % pay attention, the input F_y must follows the ISO convention and not adapted SAE as in the book
            
            % reconstruction of loaded radius from rho
            R_l = obj.R_0 - rho;
            
            % compute QFZ1, which is usually not present in tir file
            Q_FZ1 = sqrt((obj.ver_stiff.*obj.R_0./obj.F_z0).^2 - 4.* obj.Q_FZ2);
            
            R_omega = obj.R_0 .* (obj.Q_RE0 + obj.Q_V1 .* ((omega .* obj.R_0)./obj.V_0));
            
            Sfyg = (obj.Q_FYS1 + obj.Q_FYS2.*(R_l./R_omega) + obj.Q_FYS3.*(R_l./R_omega).^2).*gamma;
            
            rho_zfr = max(R_omega - R_l, 0);
            
            rtw = (1.075 - 0.5 * obj.ASPECT_RATIO) * obj.WIDTH;
            
            rho_zg = ((obj.Q_CAM1 .* R_l + obj.Q_CAM2 .* R_l.^2) .* gamma).^2 .* (rtw/8).*abs(tan(gamma)) ./ ((obj.Q_CAM1 .* R_omega + obj.Q_CAM2 .* R_omega.^2) .* gamma).^2   - (obj.Q_CAM3.* rho_zfr .* abs(gamma));
            
            rho_zg(isnan(rho_zg)) = 0;
            
            rho_z = max(rho_zfr + rho_zg, 0);
            
            fcorr = (1 + obj.Q_V2.*(obj.R_0./obj.V_0).*abs(omega) - ((obj.Q_FCX.*F_x)./obj.F_z0).^2 - ((rho_z./obj.R_0).^ obj.Q_FCY2 .* (obj.Q_FCY*(F_y - Sfyg)./obj.F_z0)).^2);
            
            % Vertical force temp
            F_z_t = fcorr.*(Q_FZ1.*(rho_z/obj.R_0) + obj.Q_FZ2.*(rho_z/obj.R_0).^2).*obj.F_z0;
            
            % Bottoming contribute
            F_z_b = obj.bott_stiff .* (rho-(obj.R_0 - obj.rim_radius - obj.bott_offst)) .* ((rho-(obj.R_0 - obj.rim_radius  - obj.bott_offst))>0);
            
            % Damping effect
            F_z_d = obj.ver_damping .* max(obj.rho_dot_min,min(obj.rho_dot_max,rho_dot)); % saturate rho_dot to -1..1
            
            % Vertical force
            
            F_z = max(0,F_z_t + F_z_b + F_z_d); %take only positive forces
            
            F_z(rho<0) = 0;
            
        end % compute_F_z
        
        
        function R_e = compute_Re(obj,rho,omega) % (See manual conf)
            % effective rolling radius
            
            R_omega = obj.R_0 .* (obj.Q_RE0 + obj.Q_V1 .* ((omega .* obj.R_0)./obj.V_0));
            
            rho_Fz0 = obj.F_z0 ./ obj.ver_stiff;
            rho_d = rho ./ rho_Fz0;
            
            R_e = R_omega - rho_Fz0 .*(obj.FREFF .* rho_d + obj.DREFF .* atan(obj.BREFF .* rho_d));
            
            R_e(isnan(R_e)) = obj.R_0;
            
        end % compute_Re
        
    end % public methods
    
    
    
    
    
    
    methods (Access = protected)
        
        function sgn = mysign(~,x)
            % Avoid sign(0) = 0
            if x==0
                sgn = 1;
            else
                sgn = sign(x);
            end
        end
        
        
        function [V_var,d_var,first_var] = common(obj,kappa,alpha,V_x,F_z,~)
            %common parameters computation
            
            V_cx = V_x;   % !! V_x (wheel center 'x' velocity)  ~  V_cx (contact path 'x' velocity) [Page 67 Book]
            
            V_sx = -kappa .* abs(V_cx); % [Eqn (4.E5) Page 181 - Book]
            
            V_sy = - tan(alpha) .* abs(V_cx); % [Eqn (2.12) Page 67 - Book]  this time with - sign to be compliant with pacejka definition (the PCJK->ISO is performed on the final force/moments)
            
            V_s = sqrt(V_sx.^2 + V_sy.^2);
            
            V_c = sqrt(V_cx.^2 + V_sy.^2);
            
            FFirst_z0 = obj.lambda_Fz0 .* obj.F_z0;
            
            df_z = (F_z - FFirst_z0)./FFirst_z0;
            
            dp_i = 0;
            
            VFirst_c = V_c + obj.epsilon_V;
            
            cosFirst_a = V_cx./VFirst_c;
            
            
            V_x(isnan(V_x)) = 0;
            V_cx(isnan(V_cx)) = 0;
            V_sx(isnan(V_sx)) = 0;
            V_sy(isnan(V_sy)) = 0;
            V_s(isnan(V_s)) = 0;
            V_c(isnan(V_c)) = 0;
            
            df_z(isnan(df_z)) = 0;
            dp_i(isnan(dp_i)) = 0;
            
            FFirst_z0(isnan(FFirst_z0)) = 0;
            VFirst_c(isnan(VFirst_c)) = 0;
            cosFirst_a(isnan(cosFirst_a)) = 0;
            
            
            % Outputs
            
            V_var.V_x = V_x;
            V_var.V_cx = V_cx;
            V_var.V_sx = V_sx;
            V_var.V_sy = V_sy;
            V_var.V_s = V_s;
            V_var.V_c = V_c;
            
            d_var.df_z = df_z;
            d_var.dp_i = dp_i;
            
            first_var.FFirst_z0 = FFirst_z0;
            first_var.VFirst_c = VFirst_c;
            first_var.cosFirst_a = cosFirst_a;
            
        end % common
        
        
        
        function Zita = zita(~, ~, ~, ~, ~, ~, ~, ~, ~, ~)
            % where turn slip phi_t may be neglected (path radius R -> Inf)
            % and camber remains small, the factors zita_i appearing in the
            % equations may be set equal to unity
            
            zita_0 = 1;
            zita_1 = 1;
            zita_2 = 1;
            zita_3 = 1;
            zita_4 = 1;
            zita_5 = 1;
            zita_6 = 1;
            zita_7 = 1;
            zita_8 = 1;
            
            Zita.zita_0 = zita_0;
            Zita.zita_1 = zita_1;
            Zita.zita_2 = zita_2;
            Zita.zita_3 = zita_3;
            Zita.zita_4 = zita_4;
            Zita.zita_5 = zita_5;
            Zita.zita_6 = zita_6;
            Zita.zita_7 = zita_7;
            Zita.zita_8 = zita_8;
            
        end % zita
        
        
        function F_x0 = compute_F_x0(obj,F_z,kappa,gamma,~,d_var,~)
            % Longitudinal Force (Pure Longitudinal slip alpha = 0)
            SHx = d_var.df_z .* obj.PHX2 + obj.PHX1;
            SVx = F_z .* (d_var.df_z .* obj.PVX2 + obj.PVX1);
            kappa__x = kappa + SHx;
            
            Cx = obj.PCX1.* obj.lambda_Cx;
            mu__x = (d_var.df_z .* obj.PDX2 + obj.PDX1) .* (-obj.PDX3 .* gamma .^ 2 + 1);
            Dx = mu__x .* F_z;
            Kxk = F_z .* (d_var.df_z .* obj.PKX2 + obj.PKX1) .* exp((obj.PKX3 .* d_var.df_z));
            Ex = (d_var.df_z .^ 2 .* obj.PEX3 + d_var.df_z .* obj.PEX2 + obj.PEX1) .* (1 - obj.PEX4);
            Bx = Kxk ./ Cx ./ Dx;
            
            F_x0 = (-Dx .* sin(Cx .* atan(-Bx .* kappa__x + Ex .* (Bx .* kappa__x - atan(Bx .* kappa__x)))) + SVx);
            
        end % compute_F_x0
        
        
        function F_x = compute_F_x_comb(obj,kappa,alpha,~,~)
            % Longitudinal Force (Combined Slip)
            
            SHxa = obj.RHX1;
            Bxa = obj.RBX1 .* (kappa .^ 2 .* obj.RBX2 .^ 2 + 1) .^ (-0.1e1 ./ 0.2e1);
            Cxa = obj.RCX1;
            Dxa = 0.1e1 ./ cos(Cxa .* atan((Bxa .* SHxa)));
            Gxa = Dxa .* cos(Cxa .* atan((Bxa .* (alpha + SHxa))));
            
            F_x =  obj.F_x0 .* Gxa;
            
        end % compute_F_x_comb
        
        
        function F_y0 = compute_F_y0(obj,F_z,alpha,gamma,~,d_var,first_var,~)
            % Lateral Force (Pure Side slip kappa = 0)
            
            gamma__s = gamma;
            SHy = d_var.df_z .* obj.PHY2 + obj.PHY3 .* gamma__s + obj.PHY1;
            SVy = F_z .* (obj.PVY1 + obj.PVY2 .* d_var.df_z + (d_var.df_z .* obj.PVY4 + obj.PVY3) .* gamma__s);
            alpha__y = alpha + SHy;
            Cy = obj.PCY1;
            mu__y = (d_var.df_z .* obj.PDY2 + obj.PDY1) .* (-obj.PDY3 .* gamma__s .^ 2 + 1);
            Dy = mu__y .* F_z;
            Ey = (d_var.df_z .* obj.PEY2 + obj.PEY1) .* (-obj.PEY4 .* gamma__s - obj.PEY3 + 1);
            Kya = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2))) .* (1 - obj.PKY3 .* abs(gamma__s));
            By = Kya ./ Cy ./ Dy;
            
            F_y0 = -Dy .* sin(Cy .* atan(-By .* alpha__y + Ey .* (By .* alpha__y - atan(By .* alpha__y)))) + SVy;
        end % compute_F_y0
        
        
        
        function F_y = compute_F_y_comb(obj,F_z,kappa,alpha,gamma,~,d_var,~)
            % Lateral Force (Combined Slip)
            
            gamma__s = gamma;
            mu__y = (d_var.df_z .* obj.PDY2 + obj.PDY1) .* (-obj.PDY3 .* gamma__s .^ 2 + 1);
            SHyk = obj.RHY1;
            DVyk = mu__y .* F_z .* (d_var.df_z .* obj.RVY2 + gamma .* obj.RVY3 + obj.RVY1) .* (alpha .^ 2 .* obj.RVY4 .^ 2 + 1) .^ (-0.1e1 ./ 0.2e1);
            SVyk = DVyk .* sin(obj.RVY5 .* atan((obj.RVY6 .* kappa)));
            Byk = obj.RBY1 .* (1 + obj.RBY2 .^ 2 .* (alpha - obj.RBY3) .^ 2) .^ (-0.1e1 ./ 0.2e1);
            Cyk = obj.RCY1;
            Dyk = 0.1e1 ./ cos(Cyk .* atan((Byk .* SHyk)));
            Gyk = Dyk .* cos(Cyk .* atan((Byk .* (kappa + SHyk))));
            
            F_y = obj.F_y0  .* Gyk + SVyk;
            
        end % compute_F_y_comb
        
        
        function M_z0 = compute_M_z0(obj,F_z,alpha,gamma,~,d_var,first_var,~)
            % Aligning Torque (Pure Side Slip kappa = 0)
            
            gamma__s = gamma;
            SHy = d_var.df_z .* obj.PHY2 + obj.PHY3 .* gamma__s + obj.PHY1;
            SVy = F_z .* (obj.PVY1 + obj.PVY2 .* d_var.df_z + (d_var.df_z .* obj.PVY4 + obj.PVY3) .* gamma__s);
            Cy = obj.PCY1;
            mu__y = (d_var.df_z .* obj.PDY2 + obj.PDY1) .* (-obj.PDY3 .* gamma__s .^ 2 + 1);
            Dy = mu__y .* F_z;
            
            Kya = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2))) .* (1 - obj.PKY3 .* abs(gamma__s));
            By = Kya ./ Cy ./ Dy;
            gamma__z = gamma;
            SHf = SHy + SVy ./ Kya;
            alpha__r = alpha + SHf;
            
            Br = By .* Cy .* obj.QBZ10 + obj.QBZ9;
            Dr = F_z .* (obj.QDZ6 + obj.QDZ7 .* d_var.df_z + (d_var.df_z .* obj.QDZ9 + obj.QDZ8) .* gamma__z) .* obj.R_0;
            
            M_z0 = Dr .* ((Br .^ 2 .* alpha__r .^ 2 + 1) .^ (-0.1e1 ./ 0.2e1)) .* cos(alpha);
            
        end % compute_M_z0
        
        
        
        function M_z = compute_M_z(obj,F_z,kappa,alpha,gamma,~,d_var,first_var,~)
            % Aligning Torque (Combined Slip)
            
            gamma__s = gamma;
            SHy = d_var.df_z .* obj.PHY2 + obj.PHY3 .* gamma__s + obj.PHY1;
            SVy = F_z .* (obj.PVY1 + obj.PVY2 .* d_var.df_z + (d_var.df_z .* obj.PVY4 + obj.PVY3) .* gamma__s);
            Cy = obj.PCY1;
            mu__y = (d_var.df_z .* obj.PDY2 + obj.PDY1) .* (-obj.PDY3 .* gamma__s .^ 2 + 1);
            Dy = mu__y .* F_z;
            Ey = (d_var.df_z .* obj.PEY2 + obj.PEY1) .* (-obj.PEY4 .* gamma__s - obj.PEY3 + 1);
            Kya = first_var.FFirst_z0 .* obj.PKY1 .* sin(obj.PKY4 .* atan((F_z ./ first_var.FFirst_z0 ./ obj.PKY2))) .* (1 - obj.PKY3 .* abs(gamma__s));
            By = Kya ./ Cy ./ Dy;
            SHyk = obj.RHY1;
            DVyk = mu__y .* F_z .* (d_var.df_z .* obj.RVY2 + gamma .* obj.RVY3 + obj.RVY1) .* (alpha .^ 2 .* obj.RVY4 .^ 2 + 1) .^ (-0.1e1 ./ 0.2e1);
            SVyk = DVyk .* sin(obj.RVY5 .* atan((obj.RVY6 .* kappa)));
            Byk = obj.RBY1 .* (1 + obj.RBY2 .^ 2 .* (alpha - obj.RBY3) .^ 2) .^ (-0.1e1 ./ 0.2e1);
            Cyk = obj.RCY1;
            Dyk = 0.1e1 ./ cos(Cyk .* atan((Byk .* SHyk)));
            Gyk = Dyk .* cos(Cyk .* atan((Byk .* (kappa + SHyk))));
            
            gamma__z = gamma;
            SHt = obj.QHZ1 + obj.QHZ2 .* d_var.df_z + (d_var.df_z .* obj.QHZ4 + obj.QHZ3) .* gamma__z;
            alpha__t = alpha + SHt;
            Bt = (d_var.df_z .^ 2 .* obj.QBZ3 + d_var.df_z .* obj.QBZ2 + obj.QBZ1) .* (1 + obj.QBZ4 .* gamma__z + obj.QBZ5 .* abs(gamma__z));
            
            alpha__y = alpha + SHy;
            
            Ct = obj.QCZ1;
            Dt = F_z .* (d_var.df_z .* obj.QDZ2 + obj.QDZ1) .* (obj.QDZ4 .* gamma__z .^ 2 + obj.QDZ3 .* gamma__z + 1) .* obj.R_0 ./ obj.F_z0;
            Et = (d_var.df_z .^ 2 .* obj.QEZ3 + d_var.df_z .* obj.QEZ2 + obj.QEZ1) .* (0.1e1 + (obj.QEZ5 .* gamma__z + obj.QEZ4) .* atan((Bt .* Ct .* alpha__t)));
            
            M_z = -((-Dy .* sin(Cy .* atan(-By .* alpha__y + Ey .* (By .* alpha__y - atan(By .* alpha__y)))) + SVy) .* Gyk + SVyk) .* Dt .* cos(Ct .* atan(-Bt .* alpha__t + Et .* (Bt .* alpha__t - atan(Bt .* alpha__t)))) .* cos(alpha) + obj.M_z0;
            
        end % compute_M_z
        
    end % private methods
    
    
end % classdef





