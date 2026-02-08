function debug_run()

    
    


end

darwin.add_recipe({
    name = "debugrun",
    description = "Make hot  reload debug run",
    outs = {"release/" .. PROJECT_NAME .. ".so"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    callback = debug_run
})