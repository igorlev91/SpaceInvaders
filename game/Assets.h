#pragma once

#include <string>

namespace Assets
{
	const std::string BasePath = "Assets/";

	namespace Config
	{
		const std::string InnerPath = "Config/";

		const std::string WindowFile = BasePath + InnerPath + "window.txt";
		const std::string GameFile = BasePath + InnerPath + "game.txt";
		const std::string PlayerFile = BasePath + InnerPath + "player.txt";

		const std::string AlienGroupFile = BasePath + InnerPath + "alien_group.txt";
		const std::string SquidFile = BasePath + InnerPath + "squid.txt";
		const std::string CrabFile = BasePath + InnerPath + "crab.txt";
		const std::string OctopusFile = BasePath + InnerPath + "octopus.txt";
		const std::string BonusAlienFile = BasePath + InnerPath + "bonus.txt";
		const std::string SecretAlienFile = BasePath + InnerPath + "a_secret.txt";
		const std::string BunkerFile = BasePath + InnerPath + "bunker.txt";

		const std::string PlayerProjectilePool = BasePath + InnerPath + "player_projectile.txt";
		const std::string AlienProjectilePool = BasePath + InnerPath + "alien_projectile.txt";
	}

	namespace Shaders
	{
		const std::string InnerPath = "Shaders/";

		const std::string ShapeName			= "shader_shape";
		const std::string ShapeVertexFile	= BasePath + InnerPath + "shape.vert";
		const std::string ShapeFragmentFile = BasePath + InnerPath + "shape.frag";

		const std::string SpriteName = "shader_sprite";
		const std::string SpriteNoColorName = "shader_sprite_no_color";
		const std::string SpriteVertexFile = BasePath + InnerPath + "sprite.vert";
		const std::string SpriteFragmentFile = BasePath + InnerPath + "sprite.frag";
		const std::string SpriteNoColorFragmentFile = BasePath + InnerPath + "sprite_no_color.frag";

		const std::string TextName = "shader_text";
		const std::string TextVertexFile = BasePath + InnerPath + "text.vert";
		const std::string TextFragmentFile = BasePath + InnerPath + "text.frag";

		const std::string ParticleShapeName = "shader_particle_shape";
		const std::string ParticleTextureName = "shader_particle_texture";
		const std::string ParticleVertexFile = BasePath + InnerPath + "particle.vert";

		const std::string ParticleShapeFragmentFile = BasePath + InnerPath + "particle_shape.frag";
		const std::string ParticleTextureFragmentFile = BasePath + InnerPath + "particle_texture.frag";
	}

	namespace Fonts
	{
		const std::string InnerPath = "Fonts/";

		const std::string TextFontName = "JerseyText";
		const std::string TextFontPath = BasePath + InnerPath + "Jersey10-Regular.ttf";

		const std::string HeadingFontName = "JerseyHeading";
		const std::string HeadingFontPath = BasePath + InnerPath + "Jersey10-Regular.ttf";
	}

	namespace Textures
	{
		const std::string InnerPath = "Sprites/";

		const std::string PlayerName = "player";
		const std::string PlayerPath = BasePath + InnerPath + "player.png";

		const std::string SquidName = "squid";
		const std::string SquidPath = BasePath + InnerPath + "squid.png";

		const std::string CrabName = "crab";
		const std::string CrabPath = BasePath + InnerPath + "crab.png";

		const std::string OctopusName = "octopus";
		const std::string OctopusPath = BasePath + InnerPath + "octopus.png";

		const std::string SecretName = "secret";
		const std::string SecretPath = BasePath + InnerPath + "secret.png";

		const std::string ExplosionName = "explosion";
		const std::string ExplosionPath = BasePath + InnerPath + "explode.png";

		const std::string BlueLaserName = "blue_laser";
		const std::string BlueLaserPath = BasePath + InnerPath + "blue_laser.png";

		const std::string RedLaserName = "red_laser";
		const std::string RedLaserPath = BasePath + InnerPath + "red_laser.png";

		const std::string WindowIcon = BasePath + InnerPath + "icon.png";
	}

	namespace Sounds
	{
		const std::string InnerPath = "Sounds/";

		const std::string AlienMoveName = "invader_move";
		const std::string AlienMove = BasePath + InnerPath + "fastinvader%d.wav";

		const std::string AlienExplosionName = "invader_explosion";
		const std::string AlienExplosion = BasePath + InnerPath + "kill.wav";

		const std::string PlayerExplosionName = "player_explosion";
		const std::string PlayerExplosion = BasePath + InnerPath + "player_explosion.wav";

		const std::string MenuNavigationName = "menu_nav";
		const std::string MenuNavigation = BasePath + InnerPath + "menu_nav.wav";

		const std::string ShootName = "shoot";
		const std::string Shoot = BasePath + InnerPath + "shoot%d.wav";

		const std::string OldShootName = "old_shoot";
		const std::string OldShoot = BasePath + InnerPath + "shoot_old.wav";

		const std::string GameOverName = "game_over";
		const std::string GameOver = BasePath + InnerPath + "game_over.wav";

		const std::string MainJingleName = "main_jingle";
		const std::string MainJingle = BasePath + InnerPath + "main.ogg";

		const std::string SecretAlienSpawnName = "secret_alien";
		const std::string SecretAlienSpawn = BasePath + InnerPath + "secret_alien_spawn.wav";
	}

	namespace Saves
	{
		const std::string BasePath = "Saves/";

		const std::string GameFile = BasePath + "game.dat";
	}
}