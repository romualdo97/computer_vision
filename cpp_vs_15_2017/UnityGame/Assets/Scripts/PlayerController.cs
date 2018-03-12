using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public Text scoreLabel;
    public Text instructionsLabel;
    public bool isAlive = true;
    public bool canPlay = false;
    public int score;

    private bool isFirstPlay = true;
    private bool canJump = false;
    private Rigidbody playerRB;
    private Vector3 jumpForce;
    private float centroid_y;
	// Use this for initialization
	void Start ()
    {
        ChromaPlugin.InitCamera();
        playerRB = GetComponent<Rigidbody>();
        jumpForce = new Vector3(0.0f, 600f, 0.0f);
	}
	
	// Update is called once per frame
	void Update ()
    {
        ChromaPlugin.UpdatePlugin();
        centroid_y = (float)ChromaPlugin.GetNormCentroid_y();
        Debug.Log(centroid_y);
        instructionsLabel.text = "INSTRUCTIONS:\ny: " + centroid_y.ToString() + "\nJUMP WHEN y < 0.8\n";
		//if (Input.GetKeyDown(KeyCode.Space) && canJump && isAlive)
  //      {
  //          Jump();
  //      }
        if (isFirstPlay && !canPlay)
        {
            if (centroid_y < 0.8)
            {
                scoreLabel.text = "Move backwards until your character stops jumping. " + centroid_y.ToString("n2") + " > 0.8";
            }
            else
            {
                scoreLabel.text = "0";
                canPlay = true;
                isFirstPlay = false;
            }
        }
        if (centroid_y < 0.8f && canJump && isAlive)
        {
            Jump();
        }
        if (canPlay)
            scoreLabel.text = "score: " + score.ToString() + " | y: " + centroid_y.ToString("n2");
    }


    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Ground")
        {
            canJump = true;
            Debug.Log("colliding ground...");
        }
        if (collision.gameObject.tag == "Obstacle")
        {
            scoreLabel.text = "you losed";
            score = 0;
            isAlive = false;
            canPlay = false;
            //isFirstPlay = true;
        }
    }

    public void Restart()
    {
        isAlive = true;
        canPlay = true;
        scoreLabel.text = score.ToString();
    }

    private void OnApplicationQuit()
    {
        ChromaPlugin.TerminatePlugin();
    }

    void Jump()
    {
        canJump = false;
        Debug.Log("Jumping...");
        playerRB.AddForce(jumpForce);
        if (canPlay)
        {
            score++;
            //scoreLabel.text = score.ToString() + " | y: " + centroid_y.ToString();
        }
    }
}
