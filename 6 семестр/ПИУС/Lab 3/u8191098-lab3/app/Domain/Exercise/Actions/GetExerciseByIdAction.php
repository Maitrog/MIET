<?php

namespace App\Domain\Exercise\Actions;

use App\Models\Exercise;

class GetExerciseByIdAction
{
    public function execute(int $exerciseId) :Exercise
    {
        return Exercise::findOrFail($exerciseId);
    }
}
