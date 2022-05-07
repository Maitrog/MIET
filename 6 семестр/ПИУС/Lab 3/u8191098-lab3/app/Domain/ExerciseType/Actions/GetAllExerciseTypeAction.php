<?php

namespace App\Domain\ExerciseType\Actions;

use App\Models\ExerciseType;

class GetAllExerciseTypeAction
{
    public function execute() : array
    {
        return ExerciseType::all()->toArray();
    }
}
