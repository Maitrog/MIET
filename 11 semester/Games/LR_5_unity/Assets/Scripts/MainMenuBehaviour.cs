using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuBehaviour : MonoBehaviour
{
    public void StartGame()
    {
        SceneManager.LoadScene("Scenes/GameScene");
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}
