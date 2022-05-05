<?php

namespace App\Domain\Exercise\Actions;

use App\Models\Exercise;

class GetAllExerciseAction
{
    public function execute() : array
    {
        return Exercise::all()->toArray();
    }
}
