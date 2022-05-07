<?php

namespace App\Domain\ExerciseType\Actions;

use App\Models\ExerciseType;

class CreateExerciseTypeAction
{
    public function execute(array $fields): ExerciseType
    {
        return ExerciseType::create($fields);
    }
}
