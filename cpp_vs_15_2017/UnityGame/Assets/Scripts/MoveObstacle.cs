using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveObstacle : MonoBehaviour
{
    public PlayerController player;
    public float speed = 0.2f;
    public float startZ;
    private Vector3 nPos;

	// Use this for initialization
	void Start ()
    {
        Restart();
	}
	
	// Update is called once per frame
	void Update ()
    {
        
        if (!player.isAlive || !player.canPlay) return;

        nPos.z -= speed;
        transform.position = nPos;

        if (transform.position.z < -20)
        {
            nPos.z = 10;
        }
	}

    public void Restart()
    {
        nPos = new Vector3(0, 0.5f, startZ);
    }
}
