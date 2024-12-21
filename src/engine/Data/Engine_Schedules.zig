const systems = @import("../Logic/ECS/ECS_Systems.zig");

pub var Start = systems.NewSchedule();

pub var PreUpdate = systems.NewSchedule();

pub var Update = systems.NewSchedule();

pub var PostUpdate = systems.NewSchedule();

pub var FixedUpdate = systems.NewSchedule();

pub var InputUpdate = systems.NewSchedule();
