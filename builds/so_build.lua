function amalgamation_build()
  
end

darwin.add_recipe({
    name = "amalgamation",
    description = "Make a single so to be used combined with CWebStudioFirmware",
    outs = {"release/" .. PROJECT_NAME .. ".so"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    requires={"amalgamation"}
    callback = amalgamation_build
})