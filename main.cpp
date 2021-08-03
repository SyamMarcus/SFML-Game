#include <SFML/Graphics.hpp>
#include <sftools/Chronometer.hpp>
#include <sftools/Common.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Detection.h"
#include "Projectile.h"
#include "Splatter.h"
#include "Menu.h"
#include "Hud.h"
#include "Background.h"
#include "DeathScreen.h"
#include "Shotgun.h"
#include "Reticle.h"
#include "Pistol.h"
#include "Smg.h"
#include "Explosion.h"
#include "Rpg.h"
#include "BruteEnemy.h"
#include "UpgradeMenu.h"

/* WAVE BASED ZOMBIE SURVIVAL WHERE PLAYER MOVES AROUND A LARGE ARENA AND USES MOUSE TO SHOOT AND AIM.
   AS ROUNDS PROGRESS, MORE ENEMIES SPAWN (MAYBE NEW TYPES), FASTER AND WITH MORE HP. BETWEEN ROUNDS 
   THE PLAYER CAN MAYBE UPGRADE GUN OR BUY NEW GUNS ASWELL AS REPLENISH HEALTH AND AMMO???. */

static const float VIEW_HEIGHT = 512.0f;
#define MAX_NUMBER_OF_wEAPONS = 2;

/*This function changes the display of the window to match the new aspect ratio of the window*/
void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	/*Creating a window ready for rendering*/
	sf::RenderWindow window(sf::VideoMode(720.0f, 720.0f), "GAME", sf::Style::Close | sf::Style::Resize);

	//Textures
	sf::Texture playerTexture; playerTexture.loadFromFile("Textures/MyPlayerFlat.png");
	sf::Texture playerLegTexture; playerLegTexture.loadFromFile("Textures/ShoesSheet.png");

	sf::Texture enemyTexture; enemyTexture.loadFromFile("Textures/Zombie1.png");
	sf::Texture bruteEnemyTexture; bruteEnemyTexture.loadFromFile("Textures/BruteEnemy1.png");

	sf::Texture projectileTexture; projectileTexture.loadFromFile("Textures/projectile1.png");

	sf::Texture car_park1; car_park1.loadFromFile("Textures/car_park1.png");

	sf::Texture bloodSplatter1; bloodSplatter1.loadFromFile("Textures/blood_splatter1.png");
	sf::Texture bloodSplatter2; bloodSplatter2.loadFromFile("Textures/blood_splatter2.png");
	sf::Texture bloodSplatter3; bloodSplatter3.loadFromFile("Textures/blood_splatter3.png");
	sf::Texture bloodSplatter4; bloodSplatter4.loadFromFile("Textures/blood_splatter4.png");
	sf::Texture bloodSplatter5; bloodSplatter5.loadFromFile("Textures/blood_splatter5.png");
	sf::Texture bloodSplatter6; bloodSplatter6.loadFromFile("Textures/blood_splatter6.png");
	sf::Texture bloodSplatter7; bloodSplatter7.loadFromFile("Textures/blood_splatter7.png");
	sf::Texture bloodSplatter8; bloodSplatter8.loadFromFile("Textures/blood_splatter8.png");
	sf::Texture bloodSplatter9; bloodSplatter9.loadFromFile("Textures/blood_splatter9.png");
	//sf::Texture bloodSplatterSheet; bloodSplatterSheet.loadFromFile("Textures/BloodSplatterSheet.png");

	sf::Texture reticle1Texture; reticle1Texture.loadFromFile("Textures/reticle1.png");

	sf::Texture box1Texture; box1Texture.loadFromFile("Textures/BoxSprite1.png");
	sf::Texture box2Texture; box2Texture.loadFromFile("Textures/BoxSprite2.png");
	
	//Sound
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Sounds/9mm_gunshot.wav");
	sf::Sound sound9mmGunshot;
	sound9mmGunshot.setBuffer(buffer);
	sound9mmGunshot.setVolume(5);


	//Player
	float playerDeathTimer = 0.0f;
	bool playerDeath = false;
	Player player(&playerTexture, &playerLegTexture,sf::Vector2u(4, 4), 0.3f, 150.0f);
	int totalPlayerHealth = player.GetHealth();
	int money = 1111;
	

	//Platforms
	Platform box1(&box1Texture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(400.0f, 300.0f));
	Platform box2(&box2Texture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(400.0f, 200.0f));
	

	//Window	
	bool exit = false;
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	//Menus
	float upgradeMenuTimer = 0.0f;
	UpgradeMenu upgradeMenu(window.getSize().x, window.getSize().y);
	float menuTimer = 0.0f;
	Menu menu(window.getSize().x, window.getSize().y);
	DeathScreen deathScreen(window.getSize().x, window.getSize().y);
	Background background(&car_park1);
	sf::Vector2i mousePos(0.0f, 0.0f);
	Hud hud(view.getCenter());
	//window.setMouseCursorVisible(false);
	//Reticle reticle1(&reticle1Texture, window.getSize());


	//Projectile
	bool projCollisionOccurred = false;
	int projCount = 0;
	float projTimer = 0.0f;
	std::vector<Projectile> projectileVec;


	//Splatter
	std::vector<Splatter> splatterVec;


	//Enemy
	bool enemyDetect = false;
	int enemyCount = 0;
	float enemyTimer = 0.0f;
	std::vector<Enemy> enemyVec;
	//BruteEnemy
	bool bruteEnemyDetect = false;
	int bruteEnemyCount = 0;
	float bruteEnemyTimer = 0.0f;
	std::vector<BruteEnemy> bruteEnemyVec;

	//Weapons
	float weaponSwitchTimer = 0.0f;
	//proj
	bool projSelected = true;
	int projMagSize = 8;
	int projAmmo = projMagSize;
	bool projReloading = false;
	//Shotgun
	int shotgunCount = 0;
	float shotgunTimer = 0.0f;
	std::vector<Shotgun> shotgunVec;
	bool shotgunSelected = false;
	//Pistol
	std::vector<Pistol> pistolVec;
	bool pistolSelected = false;
	float pistolTimer = 0.0f;
	bool pistolCollisionOccurred = false;	
	int pistolMagSize = 10;
	int pistolAmmo = pistolMagSize;
	bool pistolReloading = false;
	bool pistolOwned = false;
	//Smg
	std::vector<Smg> smgVec;
	bool smgSelected = false;
	float smgTimer = 0.0f;
	bool smgCollisionOccurred = false;
	int smgMagSize = 25;
	int smgAmmo = smgMagSize;
	bool smgReloading = false;
	bool smgOwned = false;
	//Rpg
	std::vector<Rpg> rpgVec;
	bool rpgSelected = false;
	float rpgTimer = 0.0f;
	bool rpgCollisionOccurred = false;
	int rpgMagSize = 1;
	int rpgAmmo = rpgMagSize;
	bool rpgReloading = false;
	bool rpgOwned = false;


	//Explosion
	std::vector<Explosion> explosionVec;
	float explosiveDamageTimer = 0.0f;

	//Wave
	bool waveDowntime = true;
	float waveTimer = 10.0f;
	int currentWave = 0;

	//Clock
	float deltaTime = 0.0f;
	//float chronoTime = 0.0f;
	//sf::Clock clock;
	sftools::Chronometer chrono;
	float totalTime = 0.0f;

	while (window.isOpen())
	{
		if (exit == true)
			break;
		//deltaTime = clock.restart().asSeconds();
		//chronoTime = chrono.reset(true).asSeconds();
		deltaTime = chrono.reset(true).asSeconds();
		totalTime += deltaTime;
		
		/*This checks for a window event such as closing or resizing*/
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				/*This calls the resize view function which keeps the display in the correct aspect ratio*/
				ResizeView(window, view);
				break;
			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
					case sf::Keyboard::Num1:
						//printf("Proj Selected\n");
						weaponSwitchTimer = -1.0f;
						projSelected = true;
						shotgunSelected = false;
						pistolSelected = false;
						smgSelected = false;
						rpgSelected = false;
						break;
					case sf::Keyboard::Num2:
						//printf("Shotgun Selected\n");
						weaponSwitchTimer = -1.0f;
						projSelected = false;
						shotgunSelected = true;
						pistolSelected = false;
						smgSelected = false;
						rpgSelected = false;
						break;
					case sf::Keyboard::Num3:
						if (pistolOwned)
						{
							//printf("Pistol Selected\n");
							weaponSwitchTimer = -1.0f;
							projSelected = false;
							shotgunSelected = false;
							pistolSelected = true;
							smgSelected = false;
							rpgSelected = false;
							break;
						}
						break;
					case sf::Keyboard::Num4:
						if (smgOwned)
						{
							//printf("Pistol Selected\n");
							weaponSwitchTimer = -1.0f;
							projSelected = false;
							shotgunSelected = false;
							pistolSelected = false;
							smgSelected = true;
							rpgSelected = false;
							break;
						}
						break;
					case sf::Keyboard::Num5:
						if (rpgOwned)
						{
							//printf("Pistol Selected\n");
							weaponSwitchTimer = -1.0f;
							projSelected = false;
							shotgunSelected = false;
							pistolSelected = false;
							smgSelected = false;
							rpgSelected = true;
							break;
						}
						break;
					case sf::Keyboard::B:
						if (waveDowntime == true)
						{
							chrono.toggle();
							while (true)
							{
								upgradeMenuTimer += deltaTime;
								upgradeMenu.Update(view.getCenter(), money);
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && upgradeMenuTimer >= 0.5f)
								{
									upgradeMenu.MoveUp();
									upgradeMenuTimer = 0.0f;
								}
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && upgradeMenuTimer >= 0.5f)
								{
									upgradeMenu.MoveDown();
									upgradeMenuTimer = 0.0f;
								}
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && upgradeMenuTimer >= 0.5f)
								{
									if (upgradeMenu.GetPressedItem() == 0 && pistolOwned == false) // Pistol
										if (money >= 10)
										{
											money - 10;
											pistolOwned = true;
											printf("Bought Pistol!\n");
										}
										else
											printf("Not Enough Money\n");

									if (upgradeMenu.GetPressedItem() == 1 && smgOwned == false) // Smg
										if (money >= 50)
										{
											money - 50;
											smgOwned = true;
											printf("Bought Smg!\n");
										}
										else
											printf("Not Enough Money\n");

									if (upgradeMenu.GetPressedItem() == 2 && rpgOwned == false) // Rpg
										if (money >= 120)
										{
											money - 120;
											rpgOwned = true;
											printf("Bought Rpg!\n");
										}
										else
											printf("Not Enough Money\n");

									if (upgradeMenu.GetPressedItem() == 3) // Exit Option
									{
										printf("Exit Menu\n");
										break;
									}

									upgradeMenuTimer = 0.0f;
								}
								window.clear();
								upgradeMenu.Draw(window);
								window.display();
							}
							break;
						}
					case sf::Keyboard::Escape:
						chrono.toggle();
						while (true)
						{
							menuTimer += deltaTime;
							menu.Update(view.getCenter());
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && menuTimer >= 0.2f)
							{
								menu.MoveUp();
								menuTimer = 0.0f;
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && menuTimer >= 0.2f)
							{
								menu.MoveDown();
								menuTimer = 0.0f;
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menuTimer >= 0.2f)
							{
								if (menu.GetPressedItem() == 0)
									break;
								if (menu.GetPressedItem() == 1)
									printf("options\n");
								if (menu.GetPressedItem() == 2)
								{
									exit = true;
									break;
								}
								menuTimer = 0.0f;
							}
							window.clear();
							menu.Draw(window);
							window.display();
						}
					break;
				}
			}
		}
	weaponSwitchTimer += deltaTime;
	mousePos = sf::Mouse::getPosition(window);


	//Player Death
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) || player.GetHealth() <= 0)
	{
		playerDeath = true;
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			playerDeathTimer += deltaTime;
			deathScreen.Update(view.getCenter(), deltaTime);

			window.clear();
			deathScreen.Draw(window);
			window.display();
			//std::cout << playerDeathTimer << std::endl;
		}
		break;
	}


	//Wave 
	if (enemyVec.size() <= 0)
		waveDowntime = true;
	if (waveDowntime == true)
		waveTimer -= deltaTime;
	if (waveTimer <= 0.0f)
	{
		printf("Wave Started\n");
		currentWave++;		

		for (int i = 0; i < currentWave * 2; i++)
			enemyVec.push_back(Enemy(&enemyTexture, sf::Vector2u(4, 4), 0.2f, 50.0f));

		waveTimer = 10.0f + (currentWave * 2);
		waveDowntime = false;
	}
	

	//Global enemy Timers
	enemyTimer += deltaTime;

	//Enemy Spawn and Enemy+Player Update
	Collider enemyPlayerCol = player.GetCollider();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && enemyTimer >= 0.3f)
	{		
		enemyVec.push_back(Enemy(&enemyTexture, sf::Vector2u(4, 4), 0.2f, 50.0f));
		enemyTimer = 0.0f;
	}
	for (size_t i = 0; i < enemyVec.size(); i++)
	{
		Detection enemyPlayerDet = player.GetDetection();
		enemyDetect = enemyVec[i].GetDetection().CheckDetection(enemyPlayerDet, deltaTime, 80.0f);

		enemyVec[i].Update(deltaTime, enemyDetect, player.GetPosition());

		if (enemyVec[i].GetCollider().CheckCollision(enemyPlayerCol, 0.2f))
		{
			player.Damage();
		}

		if (enemyVec.size() > 160)
		{
			enemyVec.erase(enemyVec.begin());
			enemyCount++;
			//std::cout << "ENEMY VECTOR " << enemyCount << " ERASED" << std::endl;
		}
	}
	

	//Brute Enemy
	Collider brutePlayerCol = player.GetCollider();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && enemyTimer >= 0.3f)
	{
		bruteEnemyVec.push_back(BruteEnemy(&bruteEnemyTexture, 30.0f));
		enemyTimer = 0.0f;
	}
	for (size_t i = 0; i < bruteEnemyVec.size(); i++)
	{
		Detection brutePlayerDet = player.GetDetection();
		bruteEnemyDetect = bruteEnemyVec[i].GetDetection().CheckDetection(brutePlayerDet, deltaTime, 65.0f);

		bruteEnemyVec[i].Update(deltaTime, bruteEnemyDetect, player.GetPosition());

		if (bruteEnemyVec[i].GetCollider().CheckCollision(brutePlayerCol, 0.2f))
		{
			player.Damage(2.0f);
		}

		if (bruteEnemyVec.size() > 160)
		{
			bruteEnemyVec.erase(bruteEnemyVec.begin());
			bruteEnemyCount++;
			//std::cout << "ENEMY VECTOR " << enemyCount << " ERASED" << std::endl;
		}
	}


	//Projectile Spawn and Projectile+Enemy Update
	projTimer += deltaTime;
	Random splatterChanceRan(1, 3);
	Random splatterTextureRan(1, 8);
	Random projSpreadRan(2, 10);
	Random projSpreadChanceRan(1,2);
	if ((projReloading == true && projTimer >= 0.3)) // || ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && pistolAmmo != pistolMagSize)
	{
		printf("Yeet\n");
		projAmmo = projMagSize;
		projReloading = false;
	}
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && projTimer >= 0.3f && weaponSwitchTimer >= 0.0f && projSelected && projReloading == false)
	{
		if (projAmmo <= 0 || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && projAmmo < projMagSize))
		{
			projAmmo = 0;
			projReloading = true;
			projTimer = -2.0f;
			printf("Reloading Pistol\n"); //Play reload sound
		}
		else
		{
			projectileVec.push_back(&projectileTexture);
			sound9mmGunshot.play();
			projAmmo--;
			projTimer = 0.0f;
		}

	}
	for (size_t i = 0; i < projectileVec.size(); i++)
	{
		sf::Vector2i projMousePos;
		if (projSpreadChanceRan.GetRandNum() == 1)
		{
			projMousePos.x = mousePos.x + projSpreadRan.GetRandNum();
			projMousePos.y = mousePos.y + projSpreadRan.GetRandNum();
		}
		if (projSpreadChanceRan.GetRandNum() == 2)
		{
			projMousePos.x = mousePos.x - projSpreadRan.GetRandNum();
			projMousePos.y = mousePos.y - projSpreadRan.GetRandNum();
		}
		
		projectileVec[i].Update(deltaTime, player.GetPosition(), projMousePos, window.getSize());
		
		if (projectileVec.size() > 1 && projectileVec[i].GetEraseSet())
		{
			projectileVec.erase(projectileVec.begin());
			projCount++;
			std::cout << "PROJECTILE VECTOR " << projCount << " ERASED" << std::endl;
		}

		for (size_t j = 0; j < enemyVec.size(); j++)
		{
			Collider projEnemyCol = enemyVec[j].GetCollider();
			if (projectileVec[i].GetCollider().CheckProjCollision(projEnemyCol))
			{
				projCollisionOccurred = true;
				enemyVec[j].Damage();
				//std::cout << "ENEMY " << j << " HEALTH : " << enemyVec[j].GetHealth() << std::endl;
					
				//ENEMY GRUNT SOUND CHANCE

				splatterVec.push_back(Splatter(3, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2, 
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6, 
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (enemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 5;
					enemyVec.erase(enemyVec.begin() + j);
				}
			}
		}
		for (size_t j = 0; j < bruteEnemyVec.size(); j++)
		{
			Collider projBruteEnemyCol = bruteEnemyVec[j].GetCollider();
			if (projectileVec[i].GetCollider().CheckProjCollision(projBruteEnemyCol))
			{
				projCollisionOccurred = true;
				bruteEnemyVec[j].Damage();
				//std::cout << "ENEMY " << j << " HEALTH : " << enemyVec[j].GetHealth() << std::endl;

				//ENEMY GRUNT SOUND CHANCE

				splatterVec.push_back(Splatter(3, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (bruteEnemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 8;
					bruteEnemyVec.erase(bruteEnemyVec.begin() + j);
				}
			}
		}
		if (projCollisionOccurred)
		{
			projectileVec.erase(projectileVec.begin() + i);
			projCount++;
			//std::cout << "HIT" << std::endl;
			projCollisionOccurred = false;
		}
		//else
			//std::cout << "MISSED" << std::endl;
	}

	
	//Pistol Spawn
	pistolTimer += deltaTime;
	if ((pistolReloading == true && pistolTimer >= 0.3f)) // || ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && pistolAmmo != pistolMagSize)
	{
		pistolAmmo = pistolMagSize;
		pistolReloading = false;
	}
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && pistolTimer >= 0.4f && weaponSwitchTimer >= 0.0f && pistolSelected && pistolReloading == false)
	{
		if (pistolAmmo <= 0 || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && pistolAmmo < pistolMagSize))
		{
			pistolAmmo = 0;
			pistolReloading = true;
			pistolTimer = -2.0f;
			printf("Reloading Pistol\n"); //Play reload sound
		}
		else
		{
			pistolVec.push_back(&projectileTexture);
			sound9mmGunshot.play();
			pistolAmmo--;
			pistolTimer = 0.0f;
		}
	}
	for (size_t i = 0; i < pistolVec.size(); i++)
	{
		pistolVec[i].Update(deltaTime, player.GetPosition(), mousePos, window.getSize());
		if (pistolVec.size() > 2 && pistolVec[i].GetEraseSet())
		{
			pistolVec.erase(pistolVec.begin());
		}

		for (size_t j = 0; j < enemyVec.size(); j++)
		{
			Collider pistolEnemyCol = enemyVec[j].GetCollider();
			if (pistolVec[i].GetCollider().CheckProjCollision(pistolEnemyCol))
			{
				pistolCollisionOccurred = true;
				enemyVec[j].Damage();

				splatterVec.push_back(Splatter(3, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (enemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 5;
					enemyVec.erase(enemyVec.begin() + j);
				}
			}
		}
		for (size_t j = 0; j < bruteEnemyVec.size(); j++)
		{
			Collider pistolBruteEnemyCol = bruteEnemyVec[j].GetCollider();
			if (pistolVec[i].GetCollider().CheckProjCollision(pistolBruteEnemyCol))
			{
				pistolCollisionOccurred = true;
				bruteEnemyVec[j].Damage();
				//std::cout << "ENEMY " << j << " HEALTH : " << enemyVec[j].GetHealth() << std::endl;

				//ENEMY GRUNT SOUND CHANCE

				splatterVec.push_back(Splatter(3, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (bruteEnemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 8;
					bruteEnemyVec.erase(bruteEnemyVec.begin() + j);
				}
			}
		}
		if (pistolCollisionOccurred)
		{
			pistolVec.erase(pistolVec.begin() + i);
			//std::cout << "HIT" << std::endl;
			pistolCollisionOccurred = false;
		}
	}
	

	//Smg Spawn
	smgTimer += deltaTime;
	if ((smgReloading == true && smgTimer >= 0.15f))
	{
		smgAmmo = smgMagSize;
		smgReloading = false;
	}
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && smgTimer >= 0.15f && weaponSwitchTimer >= 0.0f && smgSelected && smgReloading == false)
	{
		if (smgAmmo <= 0 || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && smgAmmo < smgMagSize))
		{
			smgAmmo = 0;
			smgReloading = true;
			smgTimer = -3.0f;
			printf("Reloading Smg\n"); //Play reload sound
		}
		else
		{		
			smgVec.push_back(&projectileTexture);
			sound9mmGunshot.play();
			smgAmmo--;
			smgTimer = 0.0f;
		}
	}
	for (size_t i = 0; i < smgVec.size(); i++)
	{
		smgVec[i].Update(deltaTime, player.GetPosition(), mousePos, window.getSize());
		if (smgVec.size() > 2 && smgVec[i].GetEraseSet())
		{
			smgVec.erase(smgVec.begin());
		}

		for (size_t j = 0; j < enemyVec.size(); j++)
		{
			Collider smgEnemyCol = enemyVec[j].GetCollider();
			if (smgVec[i].GetCollider().CheckProjCollision(smgEnemyCol))
			{
				smgCollisionOccurred = true;
				enemyVec[j].Damage();

				splatterVec.push_back(Splatter(3, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (enemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 5;
					enemyVec.erase(enemyVec.begin() + j);
				}
			}
		}
		for (size_t j = 0; j < bruteEnemyVec.size(); j++)
		{
			Collider smgBruteEnemyCol = bruteEnemyVec[j].GetCollider();
			if (smgVec[i].GetCollider().CheckProjCollision(smgBruteEnemyCol))
			{
				smgCollisionOccurred = true;
				bruteEnemyVec[j].Damage();
				//std::cout << "ENEMY " << j << " HEALTH : " << enemyVec[j].GetHealth() << std::endl;

				//ENEMY GRUNT SOUND CHANCE

				splatterVec.push_back(Splatter(3, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (bruteEnemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 8;
					bruteEnemyVec.erase(bruteEnemyVec.begin() + j);
				}
			}
		}
		if (smgCollisionOccurred)
		{
			smgVec.erase(smgVec.begin() + i);
			//std::cout << "HIT" << std::endl;
			smgCollisionOccurred = false;
		}
	}


	//Rpg Spawn
	rpgTimer += deltaTime;
	if ((rpgReloading == true && rpgTimer >= 1.0f))
	{
		rpgAmmo = rpgMagSize;
		rpgReloading = false;
	}
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && rpgTimer >= 1.0f && weaponSwitchTimer >= 0.0f && rpgSelected && rpgReloading == false)
	{
		if (rpgAmmo <= 0 || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && rpgAmmo < rpgMagSize))
		{
			rpgAmmo = 0;
			rpgReloading = true;
			rpgTimer = -2.0f;
			printf("Reloading Rpg\n"); //Play reload sound
		}
		else
		{
			rpgVec.push_back(&projectileTexture);
			//rpg sound
			rpgAmmo--;
			rpgTimer = 0.0f;
		}
	}
	for (size_t i = 0; i < rpgVec.size(); i++)
	{
		rpgVec[i].Update(deltaTime, player.GetPosition(), mousePos, window.getSize());
		if (rpgVec.size() > 2 && rpgVec[i].GetEraseSet())
		{
			rpgVec.erase(rpgVec.begin());
		}

		for (size_t j = 0; j < enemyVec.size(); j++)
		{
			Collider rpgEnemyCol = enemyVec[j].GetCollider();
			if (rpgVec[i].GetCollider().CheckProjCollision(rpgEnemyCol))
			{
				rpgCollisionOccurred = true;
				enemyVec[j].Damage();

				explosionVec.push_back(Explosion(&box1Texture, sf::Vector2f(50, 50), rpgVec[i].GetPosition()));

				splatterVec.push_back(Splatter(3, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (enemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, enemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 5;
					enemyVec.erase(enemyVec.begin() + j);
				}
			}
		}
		for (size_t j = 0; j < bruteEnemyVec.size(); j++)
		{
			Collider rpgBruteEnemyCol = bruteEnemyVec[j].GetCollider();
			if (rpgVec[i].GetCollider().CheckProjCollision(rpgBruteEnemyCol))
			{
				rpgCollisionOccurred = true;
				bruteEnemyVec[j].Damage();

				explosionVec.push_back(Explosion(&box1Texture, sf::Vector2f(50, 50), rpgVec[i].GetPosition()));
				//ENEMY GRUNT SOUND CHANCE

				splatterVec.push_back(Splatter(3, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
					&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
					&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

				if (bruteEnemyVec[j].GetAlive() == false)
				{
					splatterVec.push_back(Splatter(1, bruteEnemyVec[j].GetPosition(), &bloodSplatter1, &bloodSplatter2,
						&bloodSplatter3, &bloodSplatter4, &bloodSplatter5, &bloodSplatter6,
						&bloodSplatter7, &bloodSplatter8, &bloodSplatter9));

					if (splatterVec.size() > 30)
						splatterVec.erase(splatterVec.begin());

					money + 8;
					bruteEnemyVec.erase(bruteEnemyVec.begin() + j);
				}
			}
		}
		if (rpgCollisionOccurred)
		{
			rpgVec.erase(rpgVec.begin() + i);
			//std::cout << "HIT" << std::endl;
			rpgCollisionOccurred = false;
		}
	}


	//Shotgun Spawn and 
	shotgunTimer += deltaTime;
	if (shotgunSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && shotgunTimer >= 0.3f)
	{
		shotgunVec.push_back(&projectileTexture);
		sound9mmGunshot.play();
		shotgunTimer = 0.0f;
	}
	for (size_t i = 0; i < shotgunVec.size(); i++)
	{
		shotgunVec[i].Update(deltaTime, player.GetPosition(), mousePos, window.getSize());
		if (shotgunVec.size() > 10)
		{
			shotgunVec.erase(shotgunVec.begin());
			shotgunCount++;
			//std::cout << "PROJECTILE VECTOR " << projCount << " ERASED" << std::endl;
		}
	}

    /*This runs the Update function from the player class and then updates the current view of the
	screen which is centered on the players position. We run the collision functions second and the
	view functions after that to flickering player textures with the player animation updating after
	object or camera interactions*/

	//Other Updates
	hud.Update(view.getCenter(), view.getSize(), player.GetHealth(), totalPlayerHealth, 
		waveDowntime, currentWave, waveTimer, enemyVec.size(), money);
	if (projSelected)
		hud.gunUpdate("Proj", projAmmo, projMagSize);
	if (pistolSelected)
		hud.gunUpdate("Pistol", pistolAmmo, pistolMagSize);
	if (smgSelected)
		hud.gunUpdate("Smg", smgAmmo, smgMagSize);
	if (rpgSelected)
		hud.gunUpdate("Rpg", rpgAmmo, rpgMagSize);

	explosiveDamageTimer += deltaTime;
	for (int i = 0; i < explosionVec.size(); i++)
	{
		explosionVec[i].Update(deltaTime);

		for (size_t j = 0; j < enemyVec.size(); j++)
		{
			Collider explosionEnemyCol = enemyVec[j].GetCollider();
			if (explosionVec[i].GetCollider().CheckProjCollision(explosionEnemyCol))
			{
				enemyVec[j].Damage(3.0f);

				if (enemyVec[j].GetAlive() == false)
				{
					money + 5;
					enemyVec.erase(enemyVec.begin() + j);
				}
			}
		}

		for (size_t j = 0; j < bruteEnemyVec.size(); j++)
		{
			Collider explosionBruteEnemyCol = bruteEnemyVec[j].GetCollider();
			if (explosionVec[i].GetCollider().CheckProjCollision(explosionBruteEnemyCol))
			{
				bruteEnemyVec[j].Damage(3.0f);

				if (bruteEnemyVec[j].GetAlive() == false)
				{
					money + 8;
					bruteEnemyVec.erase(bruteEnemyVec.begin() + j);
				}
			}
		}

		Collider explosionPlayerCol = player.GetCollider();
		if (explosionVec[i].GetCollider().CheckProjCollision(explosionPlayerCol))
		{
			player.Damage();
		}

		if (explosionVec[i].GetEraseSet())
		{
			explosionVec.erase(explosionVec.begin() + i);
			//printf("yeet\n");
		}

	}

	player.Update(deltaTime, mousePos, window.getSize());
	
	//reticle1.Update(mousePos, window.getSize());
	
	/*we have to make a new collider object for the second objects collison and then use the collider object
	with another GetCollider to check if those two objects are colliding*/

	//Player and Patform Collision
	Collider col1 = player.GetCollider();
	box1.GetCollider().CheckCollision(col1, 1.0f);
	Collider col2 = player.GetCollider();
	box2.GetCollider().CheckCollision(col2, 0.5f);
	Collider col3 = box1.GetCollider();
	box2.GetCollider().CheckCollision(col3, 0.5f);


	view.setCenter(player.GetPosition());

	/*This clears the current window, sets the window view, Draws any objets to the window and
	replaces the cleared window*/
	//Window Drawing
	window.clear(); // LAST == TOP LAYER
	window.setView(view);

	background.Draw(window);

	box1.Draw(window);
	box2.Draw(window);

	for (size_t i = 0; i < splatterVec.size(); i++)
		splatterVec[i].Draw(window);

	for (size_t i = 0; i < explosionVec.size(); i++)
		explosionVec[i].Draw(window);

	for (size_t i = 0; i < enemyVec.size(); i++)
		enemyVec[i].Draw(window);
	
	for (size_t i = 0; i < bruteEnemyVec.size(); i++)
		bruteEnemyVec[i].Draw(window);

	for (size_t i = 0; i < projectileVec.size(); i++)
			projectileVec[i].Draw(window);

	for (size_t i = 0; i < pistolVec.size(); i++)
		pistolVec[i].Draw(window);

	for (size_t i = 0; i < smgVec.size(); i++)
		smgVec[i].Draw(window);

	for (size_t i = 0; i < rpgVec.size(); i++)
		rpgVec[i].Draw(window);

	for (size_t i = 0; i < shotgunVec.size(); i++)
		shotgunVec[i].Draw(window);

	player.Draw(window);
 	
	//reticle1.Draw(window);

	hud.Draw(window);
	
 	window.display();
	
	//std::cout << "deltaTime: " << deltaTime << std::endl;
	}
	return 0;
}