<?php

namespace Database\Factories;

use App\Models\Exercise;
use App\Models\Workout;
use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class SetFactory extends Factory
{
    public function definition()
    {
        return [
            'exercise_id'=> Exercise::
            inRandomOrder()->first()->id,
            'workout_id'=> Workout::
            inRandomOrder()->first()->id,
            'quantity'=> null,
            'time'=> null,
            'distance'=> null,
            'additional_weight'=> 0,
        ];
    }
}
