%
% File: TestRig_graphic_SFun.m
%

function TestRig_graphic_SFun(block)
% Level-2 MATLAB file S-function for visualizing Tire Test Rig.
setup(block)
end

% Called when the block is added to a model.
function setup(block)

% 4 input port, 0 output ports
block.NumInputPorts  = 9;
block.NumOutputPorts = 0;

block.NumDialogPrms = 22;

% Setup functional port properties
block.SetPreCompInpPortInfoToDynamic;

% Define inputs dimensions
block.InputPort(1).Dimensions = [4 4];
block.InputPort(2).Dimensions = [4 4];
block.InputPort(3).Dimensions = [4 4];
block.InputPort(4).Dimensions = [4 4];
block.InputPort(5).Dimensions = [4 4];
block.InputPort(6).Dimensions = [4 4];
block.InputPort(7).Dimensions = 1;
block.InputPort(8).Dimensions = 3;
block.InputPort(9).Dimensions = 3;

% Register block methods
block.RegBlockMethod('Start',   @Start);
block.RegBlockMethod('Outputs', @Output);

% To work in external mode
block.SetSimViewingDevice(true);

%define SAMPLE_TIME
sample_time = block.DialogPrm(1).Data;
block.SampleTimes = [sample_time, 0];

end

% Called when the simulation starts.
function Start(block)
% Check to see if we already have an instance of TestRig_graphics
ud = get_param(block.BlockHandle,'UserData');
if isempty(ud)
    vis = [];
else
    vis = ud.vis;
end

%Check if figure exists
figHandles = findobj('Type', 'figure','Name','Graphics');
if isempty(figHandles)
    figure('Name', 'Graphics','NumberTitle','off');
else
    figure(figHandles);
end

% If not, create one
if isempty(figHandles) || isempty(vis) || ~isa(vis,'TestRig_graphic') || ~vis.isAlive
    
    %Dialog port variables
    tire_data         = block.DialogPrm(2).Data;
    road_file         = block.DialogPrm(3).Data;
    rig_up_stl        = block.DialogPrm(4).Data;
    rig_up_stl_scale  = block.DialogPrm(5).Data;
    rig_low_stl       = block.DialogPrm(6).Data;
    rig_low_stl_scale = block.DialogPrm(7).Data;
    wheel_stl         = block.DialogPrm(8).Data;
    wheel_stl_scale   = block.DialogPrm(9).Data;
    en_realdim_scale  = block.DialogPrm(10).Data;
    en_trace_wheel    = block.DialogPrm(11).Data;
    en_trace_cp       = block.DialogPrm(12).Data;
    en_RF_wheel       = block.DialogPrm(13).Data;
    en_RF_cp          = block.DialogPrm(14).Data;
    en_RF_wheelHub    = block.DialogPrm(15).Data;
    en_normal         = block.DialogPrm(16).Data;
    en_forces         = block.DialogPrm(17).Data;
    en_moments        = block.DialogPrm(18).Data;
    en_P_wh           = block.DialogPrm(19).Data;
    en_P_cp           = block.DialogPrm(20).Data;
    
    % tire variables
    R_tire = tire_data.UNLOADED_RADIUS;
    B_tire = tire_data.RIM_WIDTH;
    
    % initialize RFs
    RF_up_rig   = block.InputPort(1).Data;
    RF_low_rig  = block.InputPort(2).Data;
    RF_wheel    = block.InputPort(3).Data;
    RF_cam      = block.InputPort(4).Data;
    RF_cp       = block.InputPort(5).Data;
    RF_wheelHub = block.InputPort(6).Data;
    
    vis = TestRig_graphic(rig_up_stl,                                   ...
                          rig_up_stl_scale,                             ...
                          rig_low_stl,                                  ...
                          rig_low_stl_scale,                            ...
                          wheel_stl,                                    ...
                          wheel_stl_scale,                              ...
                          RF_up_rig,                                    ...
                          RF_low_rig,                                   ...
                          RF_wheel,                                     ...
                          RF_cam,                                       ...
                          RF_cp,                                        ...
                          RF_wheelHub,                                  ...
                          R_tire,                                       ...
                          B_tire,                                       ...
                          en_realdim_scale,                             ...
                          en_trace_wheel,                               ...
                          en_trace_cp,                                  ...
                          en_RF_wheel,                                  ...
                          en_RF_cp,                                     ...
                          en_RF_wheelHub,                               ...
                          en_normal,                                    ...
                          en_forces,                                    ...
                          en_moments,                                   ...
                          en_P_wh,                                      ...
                          en_P_cp                                       ...
                          );   % initialize Testrig graphics
    
    % load road
    [~, ~, fExt] = fileparts(road_file);
    if strcmp(fExt, '.rdf')
        [Nodes,Elements,MU] = RDF_read(road_file);
    elseif strcmp(fExt, '.obj')
        obj = readObj(road_file) ;
        Nodes = obj.v;
        Elements = obj.f.v;
        MU = ones(length(Elements),1);
    else
        error('Wrong road file format');
    end
    
    Track3D(Nodes,Elements,MU);
    
else
    vis.clearTraces();
end
ud.vis = vis;

% Save it in UserData
set_param(block.BlockHandle,'UserData',ud);

save_gif          = block.DialogPrm(21).Data;
gif_folder        = block.DialogPrm(22).Data;

if save_gif
    gif_file = [gif_folder,'/','Animation.gif'];
    if ~isfolder(gif_folder)
        mkdir(gif_folder);
    end
    if isfile(gif_file)
        delete(gif_file)
    end
    frame = getframe(gcf);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
    % Initialize the GIF File
    imwrite(imind,cm,gif_file,'gif', 'Loopcount',inf);
end

end

% Called when the simulation time changes.
function Output(block)

ud = get_param(block.BlockHandle,'UserData');
vis = ud.vis;
RF_up_rig   = block.InputPort(1).Data;
RF_low_rig  = block.InputPort(2).Data;
RF_wheel    = block.InputPort(3).Data;
RF_cam      = block.InputPort(4).Data;
RF_cp       = block.InputPort(5).Data;
RF_wheelHub = block.InputPort(6).Data;
rho         = block.InputPort(7).Data;
STI_forces  = block.InputPort(8).Data;
STI_moments = block.InputPort(9).Data;
vis.step(RF_up_rig, RF_low_rig, RF_wheel, RF_cam, RF_cp, RF_wheelHub, rho, STI_forces, STI_moments);

save_gif          = block.DialogPrm(21).Data;
gif_folder        = block.DialogPrm(22).Data;
if save_gif
    gif_file = [gif_folder,'/','Animation.gif'];
    frame = getframe(gcf);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
    % Write to the GIF File
    imwrite(imind,cm,gif_file,'WriteMode','append','DelayTime',block.SampleTimes(1));
end

end