<?php

namespace App\Domain\Exercise\Actions;

use App\Models\Exercise;

class DeleteExerciseByIdAction
{
    public function execute(int $exerciseId)
    {
        $exercise = Exercise::findOrFail($exerciseId);
        $exercise->delete();

        return $exercise;
    }
}
