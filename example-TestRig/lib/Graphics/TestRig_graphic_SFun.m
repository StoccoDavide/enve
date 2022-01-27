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
block.NumInputPorts  = 4;
block.NumOutputPorts = 0;

block.NumDialogPrms = 11;

% Setup functional port properties
block.SetPreCompInpPortInfoToDynamic;

% Define inputs dimensions
block.InputPort(1).Dimensions = [4 4];
block.InputPort(2).Dimensions = [4 4];
block.InputPort(3).Dimensions = [4 4];
block.InputPort(4).Dimensions = [4 4];

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
    en_trace_wheel    = block.DialogPrm(10).Data;
    en_realdim_scale  = block.DialogPrm(11).Data;
    
    % tire variables
    R_tire = tire_data.UNLOADED_RADIUS;
    B_tire = tire_data.RIM_WIDTH;
    
    % initialize RFs
    RF_up_rig  = block.InputPort(1).Data;
    RF_low_rig = block.InputPort(2).Data;
    RF_wheel   = block.InputPort(3).Data;
    RF_cam     = block.InputPort(4).Data;
    
    if en_realdim_scale
        vis = TestRig_graphic(rig_up_stl,rig_up_stl_scale,rig_low_stl,rig_low_stl_scale,wheel_stl,wheel_stl_scale,en_trace_wheel, RF_up_rig, RF_low_rig, RF_wheel, RF_cam, R_tire, B_tire);   % initialize Testrig graphics
    else
        vis = TestRig_graphic(rig_up_stl,rig_up_stl_scale,rig_low_stl,rig_low_stl_scale,wheel_stl,wheel_stl_scale,en_trace_wheel, RF_up_rig, RF_low_rig, RF_wheel, RF_cam);   % initialize Testrig graphics
    end
    
    % load road
    [~, ~, fExt] = fileparts(road_file);
    if strcmp(fExt, '.rdf')
        [Nodes,Elements,MU] = RDF_read(road_file);
    elseif strcmp(fExt, '.obj')
        obj = readObj(fname) ;
        Nodes = obj.v;
        Elements = obj.t;
        MU = ones(1,length(Elements));
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

end

% Called when the simulation time changes.
function Output(block)

ud = get_param(block.BlockHandle,'UserData');
vis = ud.vis;
RF_up_rig  = block.InputPort(1).Data;
RF_low_rig = block.InputPort(2).Data;
RF_wheel   = block.InputPort(3).Data;
RF_cam     = block.InputPort(4).Data;
vis.step(RF_up_rig, RF_low_rig, RF_wheel, RF_cam);

end