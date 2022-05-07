<?php

namespace App\Domain\Exercise\Actions;

use App\Models\Exercise;

class PatchExerciseByIdAction
{
    public function execute(int $exerciseId, array $fields):Exercise
    {
        $exercise = Exercise::findOrFail($exerciseId);
        $exercise->update($fields);

        return $exercise;
    }
}
