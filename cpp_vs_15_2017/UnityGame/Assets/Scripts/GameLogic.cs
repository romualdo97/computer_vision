using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameLogic : MonoBehaviour
{

    public PlayerController player;
    public MoveObstacle[] obstacles;
    
	// Use this for initialization
	void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
        // restart game
        if (Input.GetKeyDown(KeyCode.R) && !player.isAlive)
        {
            player.Restart();
            for (int i = 0; i < obstacles.Length; i++)
            {
                obstacles[i].Restart();
            }
        }

        if (player.score == 0)
        {
            setObstacleSpeed(0.08f);//.1
        }

        if (player.score == 3)
        {
            setObstacleSpeed(0.1f);//.1
        }

        if (player.score == 6)
        {
            setObstacleSpeed(0.13f);
        }

        if (player.score == 8)
        {
            setObstacleSpeed(0.15f);
        }

        if (player.score == 10)
        {
            setObstacleSpeed(0.19f);
        }

        if (player.score == 13)
        {
            setObstacleSpeed(0.23f);
        }

        if (player.score == 15)
        {
            setObstacleSpeed(0.28f);
        }
    }
   
    void setObstacleSpeed(float speed)
    {
        for (int i = 0; i < obstacles.Length; i++)
        {
            obstacles[i].speed = speed;
        }
    }
}
