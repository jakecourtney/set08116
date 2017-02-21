#include <glm\glm.hpp>
#include <graphics_framework.h>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;

effect eff;
target_camera cam;
texture tex;
geometry geom;
m = mesh(geom);




bool load_content() {


  // Create triangle data



	meshes["plane"] = mesh(geometry_builder::create_plane());



	meshes["pyramid2"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid3"] = mesh(geometry_builder::create_pyramid());
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder( 20, 20));

	// create scene
	meshes["pyramid"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 7.0f, -30.0f));

	meshes["pyramid2"].get_transform().scale = vec3(8.0f, 8.0f, 8.0f);
	meshes["pyramid2"].get_transform().translate(vec3(-6.0f, 7.0f, -30.0f));

	meshes["pyramid3"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["pyramid3"].get_transform().translate(vec3(-15.0f, 7.0f, -30.0f));

	meshes["cylinder"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["cylinder"].get_transform().translate(vec3(-25.0f, 2.5f, -25.0f));
	// disk for eye smaller disk for the center to be added 
	meshes["disk"].get_transform().scale = vec3(3.0f, 1.0f, 3.0f);
	


	

	//vector<vec3> positions{ vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f)
	
  };
  // Colours
 ///vector<vec4> colours{vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)};
  // Add to the geometry
  //geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
  //geom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);

  tex = texture("check_1.png");

  // Load in shaders
  eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
  eff.add_shader("shaders/basic.frag", GL_FRAGMENT_SHADER);
  // Build effect
  eff.build();

  // Set camera properties
  cam.set_position(vec3(0.0f, 0.0f, 10.0f));
  cam.set_target(vec3(0.0f, 0.0f, 0.0f));
  cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
  return true;
}


bool update(float delta_time) {
  // Update the camera
  cam.update(delta_time);
  if (glfwGetKey(renderer::get_window(), 'W'))
  {
	  m.get_transform().position -= vec3(0.0f, 0.0f, 5.0f) * delta_time;
  }
  return true;
}

bool render() 
{
	// Create MVP matrix
	for (auto &e : meshes)
	{

		auto m = e.second;

		//mat4 M(1.0f);

	  // Bind effect
		renderer::bind(eff);
		// Get model transform from mesh
		auto	M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Render geometry
		renderer::render(geom);

		// rendering the mesh
		renderer::render(m);
	}
  
  return true;
}

void main() {
  // Create application
  app application("Graphics Coursework");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}