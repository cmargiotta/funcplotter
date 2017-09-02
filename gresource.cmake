# Used for GResource.
#
# resource_dir: Directory where the .gresource.xml is located.
# resource_file: Filename of the .gresource.xml file (just the
# filename, not the complete path).
# output_dir: Directory where the .c and .h output files are written.
# output_name: Basename of the output files (don't write extension)

function (gresource resource_dir resource_file output_dir output_name)

	_pkgconfig_invoke("glib-2.0" GLIB2 PREFIX
	  "" "--variable=prefix")
	find_program(GLIB_COMPILE_RESOURCES
	             NAMES glib-compile-resources
	             HINTS ${GLIB2_PREFIX})

	if (NOT GLIB_COMPILE_RESOURCES)
		message(FATAL "Could not find glib-compile-resources")
	endif()

	# Get the output file path
	set (output_c "${output_dir}/${output_name}.c")
	set (output_h "${output_dir}/${output_name}.h")

	# Command to compile the resources
	add_custom_command (
		OUTPUT ${output_c}
		WORKING_DIRECTORY ${resource_dir}
		COMMAND ${GLIB_COMPILE_RESOURCES}
			--generate-source
			--manual-register
			--target=${output_c} ${resource_file}
		COMMAND ${GLIB_COMPILE_RESOURCES}
			--generate-header
			--manual-register
			--target=${output_h} ${resource_file}
		DEPENDS ${resource_dir}/${resource_file}
	)

endfunction ()
