<?php

namespace App\Domain\ExerciseType\Actions;

use App\Models\ExerciseType;

class GetExerciseTypeByIdAction
{
    public function execute(int $exerciseId) :ExerciseType
    {
        return ExerciseType::findOrFail($exerciseId);
    }
}
