<?php
use Symfony\Component\Validator\Constraints as Assert;
use Symfony\Component\Validator\Mapping\ClassMetadata;

class User
{
    public int $id;
    public string $login;
    public string $email;
    public string $password;
    private $createdAt;

    public function getCreatedAt() {
        return $this->createdAt;
    }

    public static function loadValidatorMetadata(ClassMetadata $metadata)
    {
        $metadata->addPropertyConstraint('id', new Assert\NotBlank());
        $metadata->addPropertyConstraint('id', new Assert\Positive());
        $metadata->addPropertyConstraint('login', new Assert\NotBlank());
        $metadata->addPropertyConstraint('login', new Assert\NotNull());
        $metadata->addPropertyConstraint('login', new Assert\Length(array(
            'min'        => 2,
            'max'        => 27,
        )));
        $metadata->addPropertyConstraint('email', new Assert\Email(array(
            'message' => 'The email "{{ value }}" is not a valid email.',
        )));
        $metadata->addPropertyConstraint('password', new Assert\NotBlank());
        $metadata->addPropertyConstraint('password', new Assert\Length(array(
            'min'        => 8,
            'max'        => 40,
        )));
        
    }

    public function __construct(int $id, string $login, string $email, string $password)
    {
        $this->id = $id;
        $this->login = $login;
        $this->email = $email;
        $this->password = $password;
        $this->createdAt = strtotime(date('d.m.Y H.i.s'));
    }

    public function __toString()
    {
        return 'Id: ' . $this->id . " Login: " . $this->login . 
        " Email: " . $this->email . " Password: " . $this->password;
    }
}

use Symfony\Component\Validator\Validation;

$user = new User(1, 'Legenda192', 'legenda192@mail.ru', 'qwerty132fsdf');

$validator = Validation::createValidatorBuilder()
    ->addMethodMapping('loadValidatorMetadata')
    ->getValidator();
$violations = $validator->validate($user);

if (count($violations) > 0) {
    echo "Invalid user" . '<br>';
}
else {
    echo "Valid user" . '<br>';
}
