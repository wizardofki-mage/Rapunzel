// Programmer: Jason Ash
// Creation date: 22 June, 2025
// Description: Rapunzel is based on the Timber! game which is the first lesson in the book Beginning C++ Game Programming 2nd Ed. by John Horton.
// It is programmed in C++ using SFML 2.6.2 and GCC 13.1.0 MinGW (both 32 bit).
// Inputs: Enter to start the game or a new game after dying, the left and right arrow keys to attack the tower, and escape to close the window.
// Output: My Rapunzel game. The object of the game is not to get squished by Rapunzel's braids and to attack the tower as quickly as you can so you don't run out of time.
// Run: Compile the game with the correct media (graphics, sounds, and fonts) in their respective folder and make sure to have your build environment set up to build SFML projects.

#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace sf;

// Function prototypes
void updateBraids(int);

const int NUM_BRAIDS                          = 6;
Sprite braids[NUM_BRAIDS];

// Where is the player/braids? Left or right?
enum class side {LEFT, RIGHT, NONE};
side braidsPositions[NUM_BRAIDS];

int main()
{
    float       baseSpeed                   = 0.0f;
    const int   NUM_CLOUDS                  = 3;
    int         index,
                cloudInitVertPos,
                baseCloudSeed,
                baseCloudSpeedOffset,
                baseCloudHeightOffset,
                baseCloudHorizontalPos,
                baseCloudHeightAddlOffset;

    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Rapunzel!!!", Style::Fullscreen);

    // Create a texture to hold a graphic in the GPU memory
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0,0);

    // make a tower sprite
    Texture textureTower;
    textureTower.loadFromFile("graphics/wizardTower.png");
    Sprite spriteTower;
    spriteTower.setTexture(textureTower);
    spriteTower.setPosition(810, 0);

    // Prepare the fairy
    Texture textureFairy;
    textureFairy.loadFromFile("graphics/fairy.png");
    Sprite spriteFairy;
    spriteFairy.setTexture(textureFairy);
    spriteFairy.setPosition(0, 800);

    // Is the fairy currently moving?
    bool fairyActive = false;

    // How fast can the fairy fly? In pixels per second.
    float fairySpeed = baseSpeed;

    // Make 3 cloud sprites from 1 texture
    Texture textureCloud;

    // Load 1 new texture
    textureCloud.loadFromFile("graphics/cloud.png");

    // Are the clouds currently on the screen?
    bool cloudActive[NUM_CLOUDS];

    // 3 New sprites with the same texture
    Sprite spriteCloud[NUM_CLOUDS];
    // Sprite spriteCloud1;
    // Sprite spriteCloud2;
    // Sprite spriteCloud3;

    float cloudSpeed[NUM_CLOUDS];

    // Instead, use a for loop to associate the textureCloud with the array of spriteClouds
    for(index = 0; index < NUM_CLOUDS; index++)
    {
        spriteCloud[index].setTexture(textureCloud);
        spriteCloud[index].setPosition(0,cloudInitVertPos);
        cloudInitVertPos += 250;
        cloudActive[index] = false;
        cloudSpeed[index] = 0.0f;
    }

    // Variables to control time itself
    Clock clock;

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 40;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth /2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track whether the game is running
    bool paused = true;

    // Draw some text
    int score = 0;

    Text messageText;
    Text scoreText;

    // We need to choose a font
    Font font;
    font.loadFromFile("fonts/MagicSchoolOne.ttf");

    // Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    // Make these strings a really big point size
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    // Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    scoreText.setPosition(20,20);

    // Prepare 6 braids
    Texture textureBraids;
    textureBraids.loadFromFile("graphics/braid.png");

    // Set the texture for each braid sprite
    for(index = 0; index < NUM_BRAIDS; index++)
    {
        braids[index].setTexture(textureBraids);
        braids[index].setPosition(-2000, -2000);

        // Set the sprite's origin to dead center
        // We can then spin it round without changing its position
        braids[index].setOrigin(220, 20);
    }

    // Prepare the player
    Texture texturePlayerRight;
    texturePlayerRight.loadFromFile("graphics/playerRight.png");
    Sprite spritePlayerRight;
    spritePlayerRight.setTexture(texturePlayerRight);
    spritePlayerRight.setPosition(1210, 830);

    Texture texturePlayerLeft;
    texturePlayerLeft.loadFromFile("graphics/playerLeft.png");
    Sprite spritePlayerLeft;
    spritePlayerLeft.setTexture(texturePlayerLeft);
    spritePlayerLeft.setPosition(640, 830);

    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 770);

    //Line the wand up with the tree
    const float WAND_POSITION_LEFT = 700;
    const float WAND_POSITION_RIGHT = 1075;

    // Prepare the wand
    Texture textureWandRight;
    textureWandRight.loadFromFile("graphics/staffRight.png");
    Sprite spriteWandRight;
    spriteWandRight.setTexture(textureWandRight);
    spriteWandRight.setPosition(WAND_POSITION_RIGHT, 895);

    Texture textureWandLeft;
    textureWandLeft.loadFromFile("graphics/staffLeft.png");
    Sprite spriteWandLeft;
    spriteWandLeft.setTexture(textureWandLeft);
    spriteWandLeft.setPosition(WAND_POSITION_LEFT, 895);

    // The wand also starts on the left
    side wandSide = side::LEFT;

    //Prepare the flying stone block
    Texture textureBlock;
    textureBlock.loadFromFile("graphics/stoneblock.png");
    Sprite spriteBlock;
    spriteBlock.setTexture(textureBlock);
    spriteBlock.setPosition(810, 720);

    // Some other useful stone block related variables
    bool blockActive = false;
    float blockSpeedX = 1000;
    float blockSpeedY = -1500;

    // Control the player input
    bool acceptInput = false;

    // Prepare the sounds
    // The player hitting stone sound
    sf::SoundBuffer strikeBuffer;
    strikeBuffer.loadFromFile("sounds/punch-a-rock.wav");
    Sound strike;
    strike.setBuffer(strikeBuffer);

    // The player has met their death under a braid
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sounds/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    // Out of time
    SoundBuffer timesUpBuffer;
    timesUpBuffer.loadFromFile("sounds/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(timesUpBuffer);

    while(window.isOpen())
    {
        cloudInitVertPos            = 0;
        baseCloudSeed               = 10;
        baseCloudSpeedOffset        = 200;
        baseCloudHeightOffset       = 150;
        baseCloudHorizontalPos      = -200;
        baseCloudHeightAddlOffset   = 0;

        // Handle the player's input
        Event event;

        while(window.pollEvent(event))
        {
            if(event.type == Event::KeyReleased && !paused)
            {
                // Listen for key presses again
                acceptInput = true;

                // Hide the wand
                spriteWandLeft.setPosition(2000, spriteWandLeft.getPosition().y);
                spriteWandRight.setPosition(2000, spriteWandRight.getPosition().y);
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start the game
        if(Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            // Reset the time and score
            score = 0;
            timeRemaining = 6;

            // Make all the braids disappear- starting in the second position
            for(index = 0; index < NUM_BRAIDS; index++)
            {
                braidsPositions[index] = side::NONE;
            }

            // Make sure the gravestone is hidden
            spriteRIP.setPosition(675, 2000);
            acceptInput = true;
        }

        // Wrap the player controls to make sure we are accepting input
        if(acceptInput)
        {
            // First handle pressing the right cursor key
            if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                // Make sure the player is on the right
                playerSide = side::RIGHT;
                wandSide = side::RIGHT;
                score++;

                // Add to the amount of time remaining
                timeRemaining += (4 / score) +.15;

                spriteWandRight.setPosition(WAND_POSITION_RIGHT, spriteWandRight.getPosition().y);

                spritePlayerRight.setPosition(1210, 830);

                // Update the braids
                updateBraids(score);

                // Set the stone block flying to the left
                spriteBlock.setPosition(810, 720);
                blockSpeedX = -5000;
                blockActive = true;

                acceptInput = false;

                // Play striking a stone sound
                strike.play();
            }

            // Handle the left cursor key
            if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                // Make sure the player is on the left
                playerSide = side::LEFT;
                wandSide = side::LEFT;
                score++;

                // Add to the amount of time remaining
                timeRemaining += (4 / score) +.15;

                spriteWandLeft.setPosition(WAND_POSITION_LEFT, spriteWandLeft.getPosition().y);

                spritePlayerLeft.setPosition(640, 830);

                // Update the braids
                updateBraids(score);

                // Set the stone block flying to the left
                spriteBlock.setPosition(810, 720);
                blockSpeedX = 5000;
                blockActive = true;

                acceptInput = false;

                // Play striking a stone sound
                strike.play();
            }
        }

        // Update the scene
        if(!paused)
        {

            // Measure time. dt stands for delta time, which is the time between two updates.
            Time dt = clock.restart();

            // Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();

            // Size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if(timeRemaining <= 0.0f)
            {
                // Pause the game
                paused = true;

                //Change the message shown to the player
                messageText.setString("Out of time!!");

                // Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

                // play out of time sound
                outOfTime.play();
            }

            // Set up the fairy
            if(!fairyActive)
            {
                // How fast is the fairy
                srand((int)time(0));
                fairySpeed = (rand() % 200) + 200;

                // How high is the fairy?
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteFairy.setPosition(2000, height);
                fairyActive = true;
            }
            else
            {
                // Move the fairy
                spriteFairy.setPosition(spriteFairy.getPosition().x - (fairySpeed * dt.asSeconds()), spriteFairy.getPosition().y);

                // Has the fairy reached the left-hand edge of the screen?
                if(spriteFairy.getPosition().x < -100)
                {
                    // Set it up ready to be a whole new fairy next frame
                    fairyActive = false;
                }
            }

            // Manage the clouds

            for(index = 0; index < NUM_CLOUDS; index++)
            {
                if(!cloudActive[index])
                {
                    // How fast is the cloud?
                    srand((int)time(0) * baseCloudSeed);
                    cloudSpeed[index] = (rand() % baseCloudSpeedOffset);
                    float height = (rand() % baseCloudHeightOffset) - baseCloudHeightAddlOffset;
                    spriteCloud[index].setPosition(baseCloudHorizontalPos, height);
                    cloudActive[index] = true;
                }
                else
                {
                    spriteCloud[index].setPosition(spriteCloud[index].getPosition().x + (cloudSpeed[index] * dt.asSeconds()), spriteCloud[index].getPosition().y);
                    if(spriteCloud[index].getPosition().x > 1920)
                    {
                        cloudActive[index] = false;
                    }
                }
                baseCloudSeed += 10;
                baseCloudHeightOffset += 150;
                baseCloudHeightAddlOffset -= 150;
            }

            // Update the score text
            std::stringstream ss;
            ss<< "Score = " << score;
            scoreText.setString(ss.str());

            // update the branch sprites
            for(index = 0; index < NUM_BRAIDS; index++)
            {
                float height = index * 150;

                if(braidsPositions[index] == side::LEFT)
                {
                    // Move the branch to the left side
                    braids[index].setPosition(610, height);

                    // Flip the sprite round the other way
                    braids[index].setRotation(180);
                }
                else if(braidsPositions[index] == side::RIGHT)
                {
                    // Move branch to the right side
                    braids[index].setPosition(1330, height);

                    // Set the sprite rotation to normal
                    braids[index].setRotation(0);
                }
                else
                {
                    // Hide the branch
                    braids[index].setPosition(3000, height);
                }
            }

        // Handle a flying stone block
        if(blockActive)
        {
            spriteBlock.setPosition(spriteBlock.getPosition().x + (blockSpeedX * dt.asSeconds()), spriteBlock.getPosition().y + (blockSpeedY * dt.asSeconds()));

            // Has the stone block reached the right hand edge?
            if(spriteBlock.getPosition().x <-100 || spriteBlock.getPosition().x > 2000)
            {
                // Set it up ready to be a whole new stone block next frame
                blockActive = false;
                spriteBlock.setPosition(810,720);
            }
        }

        // Has the player been squashed by a braid?
        if(braidsPositions[5] == playerSide)
        {
            // death
            paused      = true;
            acceptInput = false;

            // Draw the gravestone
            spriteRIP.setPosition(600, 770);

            // Hide the player
            spritePlayerLeft.setPosition(2000, spritePlayerLeft.getPosition().y);
            spritePlayerRight.setPosition(2000, spritePlayerRight.getPosition().y);

            // Change the text of the message
            messageText.setString("SQUISHED!!");

            // Center it on the screen
            FloatRect textRect = messageText.getLocalBounds();

            messageText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));
            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

            // Play the death sound
            death.play();
        }

        } // End if(!paused)

        // Draw the scene

        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        for(index = 0; index < NUM_CLOUDS; index++)
        {
            window.draw(spriteCloud[index]);
        }

        // Draw the braids
        for(index = 0; index < NUM_BRAIDS; index++)
        {
            window.draw(braids[index]);
        }

        // Draw the tree
        window.draw(spriteTower);

        if(playerSide == side::LEFT)
        {
            window.draw(spritePlayerLeft);
            // Hide the version facing right
            spritePlayerRight.setPosition(3000, 830);
        }
        else if(playerSide == side::RIGHT)
        {
            window.draw(spritePlayerRight);
            spritePlayerLeft.setPosition(3000, 830);
        }
        // Draw the player
       // window.draw(spritePlayer);

        // Draw the wand
        if(wandSide == side::LEFT)
        {
            window.draw(spriteWandLeft);
            spriteWandRight.setPosition(3000, spriteWandRight.getPosition().y);
        }
        else if(wandSide == side::RIGHT)
        {
            window.draw(spriteWandRight);
            spriteWandLeft.setPosition(3000, spriteWandLeft.getPosition().y );
        }

        // Draw the flying stone block
        window.draw(spriteBlock);

        // Draw the gravestone
        window.draw(spriteRIP);

        // Draw the fairy
        window.draw(spriteFairy);

        // Draw the score
        window.draw(scoreText);

        // Draw the timebar
        window.draw(timeBar);

        if(paused)
        {
            // Draw our message
            window.draw(messageText);
        }

        // Show everything we just drew
        window.display();
    }
    return 0;
}

void updateBraids(int seed)
{
    // Move all the braids down one place
    for(int i = NUM_BRAIDS - 1; i > 0; i--)
    {
        braidsPositions[i] = braidsPositions[i-1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT, or NONE
    srand((int)time(0)+seed);
    int r = (rand()%5);

    switch(r)
    {
        case 0:
            braidsPositions[0] = side::LEFT;
            break;
        case 1:
            braidsPositions[0] = side::RIGHT;
            break;
        default:
            braidsPositions[0] = side::NONE;
            break;
    }
}
