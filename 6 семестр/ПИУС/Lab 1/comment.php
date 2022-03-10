<?php
include 'vendor/autoload.php';
include 'user.php';

class Comment {
    public string $msg;
    public User $user;

    public function __construct(User $user, string $msg)
    {
        $this->msg = $msg;
        $this->user = $user;
    }
}

$user1 = new User(1, 'Zhivoy192', 'asdgasfd@mail.ru', 'fsdgdsgfasd');
$user2 = new User(2, 'Myaso9', 'oinouer@mail.ru', 'qfdasgarete');
$user3 = new User(3, '0strimovza2nedeli192', 'kjdfhgoier@mail.ru', 'fasdgarwgr');

$userArray = [$user1, $user2, $user3];

$comment1 = new Comment($userArray[0], "masdgsdgsdgf");
$comment2 = new Comment($userArray[1], "ertweyhnfgdb");
$comment3 = new Comment($userArray[2], "s;glkdfngsiu");

$comments = [$comment1, $comment2, $comment3];
?>

<?php
if ($_POST) {
    $time = strtotime($_POST["datetime"]);
    $time = date('d.m.Y H.i.s', $time);
    foreach ($comments as $comment) {
        if (date('d.m.Y H.i.s', $comment->user->getCreatedAt()) > $time) {
            echo $comment->msg . '<br>';
        }
    }
}
?>
<form method="post">
    Date:
    <input type="datetime-local" name="datetime" /><br/>
    <input type="submit"/><br/>
</form>
