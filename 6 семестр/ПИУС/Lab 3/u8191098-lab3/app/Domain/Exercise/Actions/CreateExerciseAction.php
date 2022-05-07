<?php

namespace App\Domain\Exercise\Actions;

use App\Models\Exercise;

class CreateExerciseAction
{
    public function execute(array $fields): Exercise
    {
        return Exercise::create($fields);
    }
}
