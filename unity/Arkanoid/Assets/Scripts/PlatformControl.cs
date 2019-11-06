

using UnityEngine;
using System.Collections;

public class PlatformControl : MonoBehaviour {

	public GameObject ball; // Тут наш префаб шарика, как ни странно
	public Transform respawnPoint; // Точка появления шарика
	public int ballSpeed; // Скорость шарика
	public float maxPositionX;
	public float minPositionX; // Макс. и мин. позиции для платформы по оси Х
	public float speed = 10f; // Скорость платформы
	public GameObject ballClone; // Созданный шарик

	private bool isCheated = false;
	private KeyCode previous;


	void Start () 
	{
		ballClone = Instantiate (ball, respawnPoint.position, Quaternion.identity) as GameObject;
		ballClone.GetComponent<Ball> ().speed = ballSpeed;
		//		ballClone.GetComponent<Ball> ().isAlive = true;
		ballClone.GetComponent<Rigidbody2D> ().AddForce (new Vector2(Random.Range(-ballSpeed, ballSpeed), ballSpeed));
	}

	void Respawn ()
	{
		// Если не выиграл и не проиграл, создаем шарик, задаем его скорость и добавляем силу
		if(!Menedjer.win && !Menedjer.lose)
		{
			ballClone = Instantiate (ball, respawnPoint.position, Quaternion.identity) as GameObject;
			ballClone.GetComponent<Ball> ().speed = ballSpeed;
	//		ballClone.GetComponent<Ball> ().isAlive = true;
			ballClone.GetComponent<Rigidbody2D> ().AddForce (new Vector2(Random.Range(-ballSpeed, ballSpeed), ballSpeed));
		}
	}

	void Update () 
	{
		// Управление платформаой A - влево, D - вправо




		if (Input.GetKey (KeyCode.I) && previous == KeyCode.A) 
		{
			isCheated = isCheated ? false : true;
		}
		if(Input.GetKey(KeyCode.A) && previous == KeyCode.M)
		{
			previous = KeyCode.A;
		}
		if (Input.GetKey (KeyCode.M)) 
		{
			previous = KeyCode.M;
		}


		if(transform.position.x < maxPositionX && (Input.GetKey(KeyCode.D)|| Input.GetKey(KeyCode.RightArrow)))
		{
			transform.Translate(speed * Time.deltaTime, 0, 0);
		}
		else if(Input.GetKey(KeyCode.A) && transform.position.x > minPositionX|| Input.GetKey(KeyCode.LeftArrow)) 
		{
			transform.Translate(-speed * Time.deltaTime, 0, 0);
		}
		else if(isCheated)
		{
			if(Input.GetKey(KeyCode.UpArrow))
			{
				transform.Translate (0, speed * Time.deltaTime, 0);
			}
			else if(Input.GetKey(KeyCode.DownArrow))
			{
				transform.Translate (0, -speed * Time.deltaTime, 0);
			}

			if(Input.GetKeyDown(KeyCode.Space)) 
			{
				Destroy(ballClone);
				// Прежде чем создать новый, уничтожаем старый
				Respawn();
			}

			/*if(Input.GetKeyDown(KeyCode.Space)) 
			{
			//	Destroy(ballClone); // Прежде чем создать новый, уничтожаем старый
				for(int i =0; i < 20;i++)
				Respawn();
			}*/
		}
	}
}
