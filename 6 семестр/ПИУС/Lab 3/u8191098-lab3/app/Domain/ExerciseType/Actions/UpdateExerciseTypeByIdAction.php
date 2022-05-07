<?php

namespace App\Domain\ExerciseType\Actions;

use App\Models\ExerciseType;

class UpdateExerciseTypeByIdAction
{
    public function execute(int $exerciseId, array $fields):ExerciseType
    {
        $exercise = ExerciseType::findOrFail($exerciseId);
        $exercise->update($fields);

        return $exercise;
    }
}
