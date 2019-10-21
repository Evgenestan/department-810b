// NULLcode Studio © 2015
// null-code.ru

using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Menedjer : MonoBehaviour {

	public static int score;
	public static bool win;
	public static bool lose;
	public static int playerLife;
	
	public Text infoText;
	public GameObject winButton;
	public GameObject loseButton;

	void Start () 
	{
		winButton.SetActive(false);
		loseButton.SetActive(false);
		lose = false;
		win = false;
		if(Application.loadedLevel == 0) playerLife = 3;
	}

	void Update () 
	{
	}

	public void GameStart(int level)
	{
		Application.LoadLevel(Application.loadedLevel + level);
	}

	void OnGUI()
	{
		if(win)
		{
			infoText.text = "!! YOU WIN !!";
			winButton.SetActive(true);
		}
		else if(lose)
		{
			infoText.text = "!! YOU LOSE !!";
			loseButton.SetActive(true);
		}
		else
		{
			infoText.text = "Score: " + score + " / Life: " + playerLife.ToString();
		}
	}
}
