#include <cbehave/cbehave.h>

#include <config.h>
#include <config_json.h>
#include <config_old.h>


FEATURE(1, "Load default config")
	SCENARIO("Load a default config")
	{
		Config config1, config2;
		GIVEN("two configs")
		GIVEN_END

		WHEN("I load them both with defaults")
			ConfigLoadDefault(&config1);
			ConfigLoadDefault(&config2);
		WHEN_END

		THEN("they should equal each other")
			SHOULD_MEM_EQUAL(&config1, &config2, sizeof(Config));
		THEN_END
	}
	SCENARIO_END
FEATURE_END

FEATURE(2, "Save and load")
	SCENARIO("Save and load old config file")
	{
		Config config1, config2;
		GIVEN("a config file with some values, and I save the config to file in the old format")
			ConfigLoadDefault(&config1);
			config1.Game.FriendlyFire = 1;
			config1.Graphics.Brightness = 5;
			ConfigSaveOld(&config1, "tmp");
		GIVEN_END

		WHEN("I load a second config from that file")
			ConfigLoadOld(&config2, "tmp");
		WHEN_END

		THEN("the two configs should be equal")
			SHOULD_MEM_EQUAL(&config1, &config2, sizeof(Config));
		THEN_END
	}
	SCENARIO_END

	SCENARIO("Save and load a JSON config file")
	{
		Config config1, config2;
		GIVEN("a config file with some values, and I save the config to a JSON file")
			ConfigLoadDefault(&config1);
			config1.Game.FriendlyFire = 1;
			config1.Graphics.Brightness = 5;
			ConfigSaveJSON(&config1, "tmp");
		GIVEN_END

		WHEN("I load a second config from that file")
			ConfigLoadJSON(&config2, "tmp");
		WHEN_END

		THEN("the two configs should be equal")
			SHOULD_MEM_EQUAL(&config1, &config2, sizeof(Config));
		THEN_END
	}
	SCENARIO_END
FEATURE_END

FEATURE(3, "Detect config version")
	SCENARIO("Detect old config version")
	{
		Config config1, config2;
		int version;
		FILE *file;
		GIVEN("a config file with some values, and I save the config to file in the old format")
			ConfigLoadDefault(&config1);
			config1.Game.FriendlyFire = 1;
			config1.Graphics.Brightness = 5;
			ConfigSaveOld(&config1, "tmp");
		GIVEN_END

		WHEN("I detect the version, and load a second config from that file")
			file = fopen("tmp", "r");
			version = ConfigGetVersion(file);
			fclose(file);
			ConfigLoad(&config2, "tmp");
		WHEN_END

		THEN("the version should be 0, and the two configs should be equal")
			SHOULD_INT_EQUAL(version, 0);
			SHOULD_MEM_EQUAL(&config1, &config2, sizeof(Config));
		THEN_END
	}
	SCENARIO_END

	SCENARIO("Detect JSON config version")
	{
		Config config1, config2;
		int version;
		FILE *file;
		GIVEN("a config file with some values, and I save the config to file in the JSON format")
			ConfigLoadDefault(&config1);
			config1.Game.FriendlyFire = 1;
			config1.Graphics.Brightness = 5;
			ConfigSaveJSON(&config1, "tmp");
		GIVEN_END

		WHEN("I detect the version, and load a second config from that file")
			file = fopen("tmp", "r");
			version = ConfigGetVersion(file);
			fclose(file);
			ConfigLoad(&config2, "tmp");
		WHEN_END

		THEN("the version should be 1, and the two configs should be equal")
			SHOULD_INT_EQUAL(version, 1);
			SHOULD_MEM_EQUAL(&config1, &config2, sizeof(Config));
		THEN_END
	}
	SCENARIO_END
FEATURE_END

FEATURE(4, "Save config as latest format by default")
	SCENARIO("Save as JSON by default")
	{
		Config config;
		int version;
		FILE *file;
		GIVEN("a config file with some values, and I save the config to file")
			ConfigLoadDefault(&config);
			config.Game.FriendlyFire = 1;
			config.Graphics.Brightness = 5;
			ConfigSaveJSON(&config, "tmp");
		GIVEN_END

		WHEN("I detect the version")
			file = fopen("tmp", "r");
			version = ConfigGetVersion(file);
			fclose(file);
		WHEN_END

		THEN("the version should be 1")
			SHOULD_INT_EQUAL(version, 1);
		THEN_END
	}
	SCENARIO_END
FEATURE_END

FEATURE(5, "New configs not saved in old files")
	SCENARIO("New JSON config saved as old file")
	{
		Config config;
		GIVEN("a config file with new values, and I save the config to file in the old format")
			ConfigLoadDefault(&config);
			config.Sound.Footsteps = 0;
			ConfigSaveOld(&config, "tmp");
		GIVEN_END

		WHEN("I load the config from that file")
			ConfigLoad(&config, "tmp");
		WHEN_END

		THEN("the new config should have the default value")
			SHOULD_INT_EQUAL(config.Sound.Footsteps, 1);
		THEN_END
	}
	SCENARIO_END
FEATURE_END

int main(void)
{
	cbehave_feature features[] =
	{
		{feature_idx(1)},
		{feature_idx(2)},
		{feature_idx(3)},
		{feature_idx(4)},
		{feature_idx(5)}
	};

	return cbehave_runner("Config features are:", features);
}
