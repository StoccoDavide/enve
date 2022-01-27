function tire_init_cb(blk, enabled_rewind_tire, pressure_from)
% Check for upper limit source
if enabled_rewind_tire
    % Check for input block
    if strcmp(get_param([blk '/reset'],'BlockType'),'Ground')
        replace_blk([blk '/reset'],'built-in/Inport');
    end
    
    if strcmp(get_param([blk '/rewind_step'],'BlockType'),'Ground')
        replace_blk([blk '/rewind_step'],'built-in/Inport');
    end
else
    % Check for input block
    if strcmp(get_param([blk '/reset'],'BlockType'),'Inport')
        replace_blk([blk '/reset'],'built-in/Ground');
    end
    
    if strcmp(get_param([blk '/rewind_step'],'BlockType'),'Inport')
        replace_blk([blk '/rewind_step'],'built-in/Ground');
    end
end

if pressure_from == 3
    % Check for input block
    if strcmp(get_param([blk '/tire_p'],'BlockType'),'Constant')
        replace_blk([blk '/tire_p'],'built-in/Inport');
    end
    
else
    % Check for input block
    if strcmp(get_param([blk '/tire_p'],'BlockType'),'Inport')
        replace_blk([blk '/tire_p'],'built-in/Constant');
        set_param([blk '/tire_p'],'Value','tire_p')
    end
    
end
