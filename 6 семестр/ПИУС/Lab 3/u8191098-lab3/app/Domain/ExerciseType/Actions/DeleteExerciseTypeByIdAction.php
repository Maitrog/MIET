<?php

namespace App\Domain\ExerciseType\Actions;

use App\Models\ExerciseType;

class DeleteExerciseTypeByIdAction
{
    public function execute(int $exerciseId)
    {
        $exercise = ExerciseType::findOrFail($exerciseId);
        $exercise->delete();

        return $exercise;
    }
}
