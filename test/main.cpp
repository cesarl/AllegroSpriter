#include				<cstdlib>
#include				"AnimationSet.hh"

int					main()
{
  AlSpriter::AnimationSet		test;
  ALLEGRO_DISPLAY			*display;

  al_init();
  al_init_image_addon();
  display = al_create_display(1000, 600);

  test.loadFromFile("assets/hero/BetaFormatHero.SCML", "assets/hero/");

  int i = 0;
  while (i < 1000)
    {
      test.draw();
      test.update(al_get_time());
      al_rest(1.0f / 60.0f);
      al_flip_display();
      al_clear_to_color(al_map_rgb(0,0,0));
      ++i;
    }

  al_shutdown_image_addon();
  al_destroy_display(display);
  return EXIT_SUCCESS;
}
