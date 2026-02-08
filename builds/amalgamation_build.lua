function amalgamation_build()
    print("\tStarting amalgamation build")

    -- Generate amalgamation from main.c
    local runtime = darwin.camalgamator.generate_amalgamation("main.c")
    runtime = "#define DEFINE_DEPENDENCIES\n" .. runtime

    -- Write to release directory
    darwin.dtw.write_file("release/" .. PROJECT_NAME .. ".c", runtime)

    print("\tAmalgamation build completed")
end

darwin.add_recipe({
    name = "amalgamation",
    description = "Make a single file amalgamation of the project",
    outs = {"release/" .. PROJECT_NAME .. ".c"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    callback = amalgamation_build
})