using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ExitSceneBehaviour : MonoBehaviour
{
    private void Start()
    {
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
    }

    public void RestartGame()
    {
        SceneManager.LoadScene("Scenes/GameScene");
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}
